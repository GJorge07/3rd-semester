#include "player.h"
#include "game.h"
#include <allegro5/allegro_image.h>


void init_player(Player *player, int x, int y) {

    player->x           = x;
    player->y           = y;
    player->largura     = PLAYER_WIDTH;
    player->altura      = PLAYER_HEIGHT;
    player->vida        = PLAYER_LIFE;
    player->vel_y       = 0;
    player->on_ground   = 1;
    player->on_platform = 0;
    player->facing_left = 0;
    player->estado         = PLAYER_PARADO;
    player->crouch_timer   = 0;
    player->anim_frame     = 0;
    player->anim_timer     = 0;

    player->sprite_sheet = al_load_bitmap("assets/images/personagem.jpg"); /*imagem do personagem em todas as poses*/

    if (player->sprite_sheet)    
        al_convert_mask_to_alpha(player->sprite_sheet, al_map_rgb(255, 255, 255)); /*tira fundo branco*/

    if (player->sprite_sheet) {   /*Define as regiões da sprite sheet usadas em cada animação*/

        int fh = al_get_bitmap_height(player->sprite_sheet) / 3;

        player->sprite_andando[0] = al_create_sub_bitmap(player->sprite_sheet,   75, 0, 858, fh);
        player->sprite_andando[1] = al_create_sub_bitmap(player->sprite_sheet,  994, 0, 715, fh);
        player->sprite_andando[2] = al_create_sub_bitmap(player->sprite_sheet, 1866, 0, 662, fh);
        player->sprite_andando[3] = al_create_sub_bitmap(player->sprite_sheet, 2588, 0, 701, fh);
        player->sprite_andando[4] = al_create_sub_bitmap(player->sprite_sheet, 3333, 0, 795, fh);
        player->sprite_andando[5] = al_create_sub_bitmap(player->sprite_sheet, 4213, 0, 659, fh);

        player->sprite_parado = al_create_sub_bitmap(player->sprite_sheet,   94, fh, 691, fh);
        player->sprite_abaixado = al_create_sub_bitmap(player->sprite_sheet,  850, fh, 662, fh);
        player->sprite_pulando = al_create_sub_bitmap(player->sprite_sheet, 4206, fh, 663, fh);
        player->sprite_andando_agachado[0] = al_create_sub_bitmap(player->sprite_sheet,  850, fh + 28,  662, 1410);
        player->sprite_andando_agachado[1] = al_create_sub_bitmap(player->sprite_sheet, 3378, fh + 120, 679, 1318);

        /*Linha 2 (y=2*fh): frames dedicados para escalada*/
        player->sprite_escalando[0] = al_create_sub_bitmap(player->sprite_sheet,   75, 2*fh, 858, fh);
        player->sprite_escalando[1] = al_create_sub_bitmap(player->sprite_sheet, 1866, 2*fh, 662, fh);

    }
}


void update_player(Player *player, int move_left, int move_right, int agachado, int sobre_buraco, int escalando) {

    /*Se o jogador está apertando para escalar e ainda não chegou na plataforma, então ignora a física normal e move o personagem para cima*/
    if (escalando && !player->on_platform) {

        player->estado    = PLAYER_ESCALANDO;
        player->on_ground = 0;
        player->vel_y     = 0;
        player->facing_left = 0;
        player->x = PLATFORM_LEFT - player->largura;/*Trava x na posição da escada pra parecer que está se segurando*/
        player->y -= CLIMB_SPEED;
        /*Animação: alterna entre frame de pulo e parado*/
        player->anim_timer++;

        if (player->anim_timer >= 10) {

            player->anim_timer = 0;
            player->anim_frame = (player->anim_frame + 1) % 2;

        }

        /*Chegou ao topo da escada*/
        if (player->y <= PLATFORM_Y - player->altura) {

            player->y = PLATFORM_Y - player->altura;
            player->on_platform = 1;
            player->on_ground   = 1;

        }
        return;
    }

    /*Animação ao estar agachado*/
    if (agachado && player->on_ground) {

        player->estado  = PLAYER_ABAIXADO;
        player->largura = PLAYER_WIDTH;
        player->altura  = PLAYER_CROUCH_H;

        if (player->crouch_timer < 8) 
            player->crouch_timer++;
        if (move_left)  
            player->x -= PLAYER_SPEED;
        if (move_right) 
            player->x += PLAYER_SPEED;
        if (move_left  && !move_right) 
            player->facing_left = 1;
        if (move_right && !move_left)  
            player->facing_left = 0;

    } else {

        /*Se não está agachado, volta ao normal*/
        player->crouch_timer = 0; 

        player->largura = PLAYER_WIDTH;
        player->altura  = PLAYER_HEIGHT;

        if (move_left)  
            player->x -= PLAYER_SPEED;
        if (move_right) 
            player->x += PLAYER_SPEED;

        /*Atualiza direção que o player está olhando*/
        if (move_left && !move_right)  
            player->facing_left = 1;
        if (move_right && !move_left)  
            player->facing_left = 0;

        /*Atualiza estado do player*/
        if (!player->on_ground)
            player->estado = PLAYER_PULANDO;
        else if (move_left || move_right)
            player->estado = PLAYER_ANDANDO;
        else
            player->estado = PLAYER_PARADO;
    }

    /*Limites do nível*/
    if (player->x < 0)
        player->x = 0;
    if (player->x + player->largura > LEVEL_WIDTH)
        player->x = LEVEL_WIDTH - player->largura;

    /*Gravidade*/
    player->vel_y += GRAVITY;
    player->y     += (int)player->vel_y;

    /*Chão: usa PLATFORM_Y quando na plataforma, GROUND_Y no chão normal*/
    int floor_y = player->on_platform ? PLATFORM_Y : GROUND_Y;

    if (player->y + player->altura >= floor_y) {

        if (player->on_platform || !sobre_buraco) {

            player->y         = floor_y - player->altura;
            player->vel_y     = 0;
            player->on_ground = 1;
        }
    }

    /*Atualiza os frames das animações do personagem */
    if (player->estado == PLAYER_ANDANDO) {

        player->anim_timer++;
        if (player->anim_timer >= 6) {

            player->anim_timer = 0;
            player->anim_frame = (player->anim_frame + 1) % WALK_FRAMES;

        }

    } else if (player->estado == PLAYER_ABAIXADO && (move_left || move_right)) {

        player->anim_timer++;
        if (player->anim_timer >= 8) {

            player->anim_timer = 0;
            player->anim_frame = (player->anim_frame + 1) % 2;

        }

    } else {

        player->anim_frame = 0;
        player->anim_timer = 0;

    }
}


void jump_player(Player *player) {

    if (player->on_ground && player->estado != PLAYER_ABAIXADO) {

        player->vel_y     = JUMP_FORCE;
        player->on_ground = 0;

    }
}


void draw_player(Player *player, float camera_x) {

    ALLEGRO_BITMAP *sprite = NULL;
    int flags = 0;

    /*Escolhe qual sprite será desenhado de acordo com o estado do jogador */
    if (player->estado == PLAYER_ABAIXADO) {

        if (player->crouch_timer < 8)
            sprite = player->sprite_pulando;
        else
            sprite = player->sprite_andando_agachado[player->anim_frame % 2];

    } else if (player->estado == PLAYER_PULANDO)
        sprite = player->sprite_pulando;

    else if (player->estado == PLAYER_ESCALANDO) {
        sprite = player->sprite_escalando[player->anim_frame % 2];

    } else if (player->estado == PLAYER_ANDANDO)
        sprite = player->sprite_andando[player->anim_frame];

    else
        sprite = player->sprite_parado;

    /*Espelha horizontalmente quando virado para a esquerda*/
    if (player->facing_left)
        flags = ALLEGRO_FLIP_HORIZONTAL;

    al_draw_scaled_bitmap(
        sprite,
        0, 0,
        al_get_bitmap_width(sprite),
        al_get_bitmap_height(sprite),
        player->x - camera_x,
        player->y,
        player->largura,
        player->altura,
        flags
    );
}


void destroy_player(Player *player) {

    if (player->sprite_sheet) {

        if (player->sprite_parado)
            al_destroy_bitmap(player->sprite_parado);
        if (player->sprite_abaixado) 
            al_destroy_bitmap(player->sprite_abaixado);
        if (player->sprite_pulando)  
            al_destroy_bitmap(player->sprite_pulando);

        for (int i = 0; i < WALK_FRAMES; i++)
            if (player->sprite_andando[i]) 
                al_destroy_bitmap(player->sprite_andando[i]);
        for (int i = 0; i < 2; i++)
            if (player->sprite_andando_agachado[i]) 
                al_destroy_bitmap(player->sprite_andando_agachado[i]);
        for (int i = 0; i < 2; i++)
            if (player->sprite_escalando[i]) 
                al_destroy_bitmap(player->sprite_escalando[i]);

        al_destroy_bitmap(player->sprite_sheet);

    } else {

        if (player->sprite_parado) 
            al_destroy_bitmap(player->sprite_parado);
    }
}
