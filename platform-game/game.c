#include "game.h"
#include "player.h"
#include "map.h"
#include "obstacle.h"
#include "colision.h"
#include "hud.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>


    ALLEGRO_TIMER*       timer = NULL;
    ALLEGRO_EVENT_QUEUE* queue = NULL;
    ALLEGRO_DISPLAY*     disp  = NULL;

    Player   player;
    Obstacle obstacles[NUM_OBSTACULOS];

    float camera_x   = 0;
    int   game_state = GAME_MENU;


int init_game() {

    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    timer = al_create_timer(1.0 / 30.0);
    queue = al_create_event_queue();
    disp  = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!timer || !queue || !disp)
        return 0;

    ALLEGRO_FONT *loading_font = al_load_ttf_font("/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf", 40, 0); /*pro "CARREGANDO..."*/

    draw_carregando(loading_font);
    al_destroy_font(loading_font);

    init_player(&player, 100, GROUND_Y - PLAYER_HEIGHT);
    init_obstacles(obstacles, NUM_OBSTACULOS);
    init_hud();
    init_map();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    return 1;
}


void game_loop() {

    ALLEGRO_EVENT event;

    char running     = 1;
    int  move_left   = 0;
    int  move_right  = 0;
    int  agachado    = 0;
    int  escalando   = 0;
    int  grupo_atual = 0;
    int  game_section = GAME_SECTION_SURFACE;

    /*Checkpoints de superfície ->controla quando um obstáculo aparece*/
    int checkpoints[] = {700, 1600, 2550, 3488};

    /*Blocos do trecho final*/
    int blocos_x[] = {4250, 4450, 4660, 4860};
    int blocos_y[] = {680,  580,  480,  370 };
    int blocos_w[] = {150,  140,  140,  200 };   /*último bloco grande, vai até x=5060*/
    int bloco_h    = 22;
    int num_blocos = 4;
    int bloco_timer[4] = {0, 0, 0, 0};  /*conta frames desde que o player pisou*/
    int bloco_ativo[4] = {1, 1, 1, 1};  /*0 = desmoronado*/

    while (running) {

        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {

            al_clear_to_color(al_map_rgb(0, 0, 0));

            /* MENU*/
            if (game_state == GAME_MENU) 
                draw_menu();

            /*JOGO*/
            else if (game_state == GAME_PLAYING) {

                /*Quando sobe pela escada no subsolo, retorna à superfície*/
                if (player.on_platform && game_section == GAME_SECTION_SUBSOLO) {

                    game_section      = GAME_SECTION_SURFACE;
                    player.on_platform = 0;
                    player.y          = GROUND_Y - player.altura;
                    player.on_ground  = 1;
                    escalando         = 0;

                    /*Desativa obstáculos do subsolo*/
                    for (int i = 0; i < NUM_OBSTACULOS; i++)
                        if (obstacles[i].section == GAME_SECTION_SUBSOLO)
                            obstacles[i].ativo = 0;

                }

                /*Detecta buraco (superfície)*/
                int sobre_buraco = 0;

                if (game_section == GAME_SECTION_SURFACE && obstacles[6].ativo) {

                    if (player.x + player.largura > obstacles[6].x &&
                        player.x < obstacles[6].x + obstacles[6].largura)
                        sobre_buraco = 1;

                }

                update_player(&player, move_left, move_right, agachado, sobre_buraco, escalando);
                update_obstacles(obstacles, NUM_OBSTACULOS, game_section, camera_x);

                /*Colisão com blocos e tempo de desmoronamento*/
                if (game_section == GAME_SECTION_SURFACE) {

                    for (int bi = 0; bi < num_blocos; bi++) {

                        if (!bloco_ativo[bi]) 
                            continue;

                        if (player.x + player.largura > blocos_x[bi] &&
                            player.x < blocos_x[bi] + blocos_w[bi]) {

                            int player_bottom = player.y + player.altura;
                            int bloco_topo    = blocos_y[bi];

                            if (player.vel_y >= 0 &&
                                player_bottom >= bloco_topo &&
                                player_bottom <= bloco_topo + bloco_h + 15) {

                                player.y         = bloco_topo - player.altura;
                                player.vel_y     = 0;
                                player.on_ground = 1;

                            }
                        }

                        /*Todos os blocos desmoronam*/
                        if (bi < num_blocos) {

                            int on_block = (player.x + player.largura > blocos_x[bi] &&
                                            player.x < blocos_x[bi] + blocos_w[bi] &&
                                            player.y + player.altura >= blocos_y[bi] - 1 &&
                                            player.y + player.altura <= blocos_y[bi] + bloco_h + 1);

                            if (on_block || bloco_timer[bi] > 0) {

                                bloco_timer[bi]++;

                                if (bloco_timer[bi] >= 90) {

                                    bloco_ativo[bi] = 0;
                                    bloco_timer[bi] = 0;

                                }
                            }
                        }
                    }

                    /*Regeneração dos blocos caídos (3 segundos depois)*/
                    for (int bi = 0; bi < num_blocos; bi++) {

                        if (!bloco_ativo[bi]) {

                            bloco_timer[bi]++;

                            if (bloco_timer[bi] >= 90) {

                                bloco_ativo[bi] = 1;
                                bloco_timer[bi] = 0;

                            }
                        }
                    }
                }

                /*Player caiu no buraco → entra no subsolo*/
                if (game_section == GAME_SECTION_SURFACE && player.y > SCREEN_HEIGHT) {

                    game_section = GAME_SECTION_SUBSOLO;
                    obstacles[6].ativo = 0;       /*desativa o buraco*/
                    obstacles[8].ativo = 1;       /*ativa o inimigo do subsolo*/
                    obstacles[8].x = 3100;        /*começa atrás do player*/
                    obstacles[8].anim_frame = 0;
                    obstacles[15].ativo = 1;       /*morcego 1*/
                    obstacles[15].x = 3900;
                    obstacles[16].ativo = 1;       /*morcego 2*/
                    obstacles[16].x  = 4150;
                    obstacles[19].ativo = 1;       /*morcego 3*/
                    obstacles[19].x  = 4400;
                    obstacles[21].ativo = 1;       /*coração subsolo*/
                    player.x = 3450;               /*pousa um pouco à frente do buraco*/
                    player.y = GROUND_Y - player.altura;
                    player.vel_y = 0;
                    player.on_ground = 1;
                    escalando = 0;

                }

                /*Colisões*/
                for (int i = 0; i < NUM_OBSTACULOS; i++) {

                    if (!obstacles[i].ativo) 
                        continue;
                    if (obstacles[i].section != game_section) 
                        continue;
                    if (obstacles[i].tipo == BURACO) 
                        continue;
                    if (obstacles[i].tipo == ESCADA) 
                        continue;

                    if (check_colision(player.x, player.y, player.largura, player.altura,
                                       obstacles[i].x, obstacles[i].y,
                                       obstacles[i].largura, obstacles[i].altura)) {

                        if (obstacles[i].tipo == CORACAO) { /*Se for coração ganha vida, se não, perde*/

                            if (player.vida < PLAYER_LIFE) 
                                player.vida++;

                        } else {

                            player.vida--;

                        }

                        obstacles[i].ativo = 0;
                    }
                }

                /*Progressão de obstáculos*/
                if (game_section == GAME_SECTION_SURFACE &&
                    grupo_atual <= 3 && player.x > checkpoints[grupo_atual]) {

                    grupo_atual++;

                    if (grupo_atual <= 3) {

                        for (int i = 0; i < NUM_OBSTACULOS; i++) {

                            if (obstacles[i].grupo == grupo_atual &&
                                obstacles[i].section == GAME_SECTION_SURFACE)
                                obstacles[i].ativo = 1;

                        }
                    }
                    /*Pássaros só existem antes dos copos*/
                    if (grupo_atual == 1) {

                        for (int i = 0; i < NUM_OBSTACULOS; i++)
                            if (obstacles[i].tipo == PASSARO)
                                obstacles[i].ativo = 0;

                    }
                }

                if (player.vida <= 0)
                    game_state = GAME_LOST;

                /*Vitória: escala os blocos e chega ao topo direito*/
                if (game_section == GAME_SECTION_SURFACE &&
                    player.x + player.largura >= LEVEL_WIDTH &&
                    player.y + player.altura <= 380)
                    game_state = GAME_WON;

                /*Câmera*/
                camera_x = player.x - 200;

                if (camera_x < 0) 
                    camera_x = 0;

                if (camera_x > LEVEL_WIDTH - SCREEN_WIDTH)
                    camera_x = LEVEL_WIDTH - SCREEN_WIDTH;

                draw_map(camera_x, game_section);

                /*Desenha blocos do final e efeito desmoronando*/
                if (game_section == GAME_SECTION_SURFACE) {

                    for (int bi = 0; bi < num_blocos; bi++) {

                        if (!bloco_ativo[bi]) 
                            continue;

                        float bx = blocos_x[bi] - camera_x;
                        int   by = blocos_y[bi];
                        int   bw = blocos_w[bi];
                        int   crumbling = (bloco_timer[bi] >= 60);

                        if (crumbling)
                            bx += (bloco_timer[bi] % 4 < 2) ? 2.0f : -2.0f;

                        ALLEGRO_COLOR c_body = crumbling ? al_map_rgb(200,  80, 20) : al_map_rgb(160, 100, 40);
                        ALLEGRO_COLOR c_top  = crumbling ? al_map_rgb(230, 120, 40) : al_map_rgb(210, 155, 75);
                        ALLEGRO_COLOR c_bot  = crumbling ? al_map_rgb(100,  30,  5) : al_map_rgb( 90,  52, 12);
                        ALLEGRO_COLOR c_side = crumbling ? al_map_rgb(210, 100, 30) : al_map_rgb(195, 140, 60);

                        al_draw_filled_rectangle(bx, by, bx + bw, by + bloco_h, c_body);
                        al_draw_filled_rectangle(bx, by, bx + bw, by + 5,       c_top);
                        al_draw_filled_rectangle(bx, by + bloco_h - 5, bx + bw, by + bloco_h, c_bot);
                        al_draw_filled_rectangle(bx, by, bx + 5, by + bloco_h,  c_side);

                    }
                }

                draw_obstacles(obstacles, NUM_OBSTACULOS, camera_x, game_section);
                draw_player(&player, camera_x);
                draw_hud(&player);
            }

            /*VITÓRIA*/
            else if (game_state == GAME_WON) 
                draw_vitoria();

            /*DERROTA*/
            else if (game_state == GAME_LOST) 
                draw_derrota();

            /*PAUSA*/
            else if (game_state == GAME_PAUSED) 
                draw_pausa();

            al_flip_display();

        }

        /*Teclas e suas respectivas funções dos menus*/
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
            running = 0;

        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

            if (game_state == GAME_MENU) {

                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                    game_state = GAME_PLAYING;
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    running = 0;

            }

            if (game_state == GAME_PAUSED) {

                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                    game_state = GAME_PLAYING;
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    game_state = GAME_LOST;

            }

            /*Reinicio do jogo caso ganhe ou perca*/
            if (game_state == GAME_WON || game_state == GAME_LOST) {

                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {

                    destroy_player(&player);
                    destroy_obstacles(obstacles, NUM_OBSTACULOS);

                    init_player(&player, 100, GROUND_Y - PLAYER_HEIGHT);
                    init_obstacles(obstacles, NUM_OBSTACULOS);

                    camera_x     = 0;
                    grupo_atual  = 0;
                    escalando    = 0;
                    move_left    = 0;
                    move_right   = 0;
                    agachado     = 0;
                    game_section = GAME_SECTION_SURFACE;
                    game_state   = GAME_PLAYING;

                    for (int bi = 0; bi < num_blocos; bi++) {

                        bloco_timer[bi] = 0;
                        bloco_ativo[bi] = 1;

                    }
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    running = 0;
            }

            /*Teclas durante o jogo*/
            if (game_state == GAME_PLAYING) {

                if (event.keyboard.keycode == ALLEGRO_KEY_A || event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                    move_left = 1;

                if (event.keyboard.keycode == ALLEGRO_KEY_D || event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                    move_right = 1;

                if (event.keyboard.keycode == ALLEGRO_KEY_S || event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                    agachado = 1;

                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
                    jump_player(&player);

                /*Escalar (Só na escada)*/
                if (event.keyboard.keycode == ALLEGRO_KEY_W || event.keyboard.keycode == ALLEGRO_KEY_UP) {
                        
                    if (game_section == GAME_SECTION_SUBSOLO &&
                        !player.on_platform && player.on_ground &&
                        player.x + player.largura >= PLATFORM_LEFT - 80 &&
                        player.x <= PLATFORM_LEFT + 80)
                        escalando = 1;
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_P)
                    game_state = GAME_PAUSED;
            }
        }

        else if (event.type == ALLEGRO_EVENT_KEY_UP) {

            if (event.keyboard.keycode == ALLEGRO_KEY_A || event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                move_left = 0;

            if (event.keyboard.keycode == ALLEGRO_KEY_D ||  event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                move_right = 0;

            if (event.keyboard.keycode == ALLEGRO_KEY_S || event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                agachado = 0;

            if (event.keyboard.keycode == ALLEGRO_KEY_W || event.keyboard.keycode == ALLEGRO_KEY_UP)
                escalando = 0;
        }
    }
}


void game_destroy() {

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    destroy_obstacles(obstacles, NUM_OBSTACULOS);
    destroy_player(&player);
    destroy_hud();
    destroy_map();

}
