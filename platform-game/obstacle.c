#include <stdio.h>
#include "obstacle.h"
#include "player.h"
#include "game.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

void init_obstacles(Obstacle *obstacles, int num_obstacles) {

    if (num_obstacles < 22)
        return;

    /*Zera tudo antes de começar*/
    for (int i = 0; i < num_obstacles; i++) {

        obstacles[i].anim_frame   = 0;
        obstacles[i].anim_timer   = 0;
        obstacles[i].sprite_sheet = NULL;
        obstacles[i].sprite       = NULL;
        obstacles[i].section      = GAME_SECTION_SURFACE;

        for (int f = 0; f < 15; f++)
            obstacles[i].run_frames[f] = NULL;
    }

    /*Pássaros voando na altura da cabeça (exige agachar)*/
    int bird_slots[] = {0, 11, 12};
    int bird_x[]     = {1500, 1700, 1900};

    for (int b = 0; b < 3; b++) {

        int i = bird_slots[b];
        
        obstacles[i].x       = bird_x[b];
        obstacles[i].y       = 490;
        obstacles[i].largura = 110;
        obstacles[i].altura  = 165;
        obstacles[i].tipo    = PASSARO;
        obstacles[i].ativo   = 1;
        obstacles[i].grupo   = 0;
        obstacles[i].vel_x   = -7;
        obstacles[i].vel_y   = bird_x[b];  /*reset x*/
        obstacles[i].angulo  = 0;
        obstacles[i].section = GAME_SECTION_SURFACE;
        obstacles[i].run_frames[0] = al_load_bitmap("assets/images/bird_0.png");
        obstacles[i].run_frames[1] = al_load_bitmap("assets/images/bird_1.png");
        obstacles[i].run_frames[2] = al_load_bitmap("assets/images/bird_2.png");
    }

    /*Copos caindo*/
    int copo_x[] = {1300, 1390, 1480, 1570};
    int copo_y[] = {-200, -500, -800, -1100};

    for (int c = 0; c < 4; c++) {
        int i = c + 1;
        obstacles[i].x       = copo_x[c];
        obstacles[i].y       = copo_y[c];
        obstacles[i].largura = 46;
        obstacles[i].altura  = 94;
        obstacles[i].tipo    = COPO;
        obstacles[i].ativo   = 0;
        obstacles[i].grupo   = 1;
        obstacles[i].vel_x   = 0;
        obstacles[i].vel_y   = 7;
        obstacles[i].angulo  = 0;
        obstacles[i].section = GAME_SECTION_SURFACE;
        obstacles[i].sprite  = al_load_bitmap("assets/images/copo.png");
    }

    /*Bolas rolando*/
    int bola_slots[] = {5, 9, 10};
    int bola_x[]     = {2400, 2700, 3000};
    int bola_reset[] = {2700, 3000, 3300};

    for (int b = 0; b < 3; b++) {
        int i = bola_slots[b];
        obstacles[i].x       = bola_x[b];
        obstacles[i].y       = 662;
        obstacles[i].largura = 100;
        obstacles[i].altura  = 100;
        obstacles[i].tipo    = BOLA;
        obstacles[i].ativo   = 0;
        obstacles[i].grupo   = 2;
        obstacles[i].vel_x   = -3;
        obstacles[i].vel_y   = bola_reset[b];  /*reset x*/
        obstacles[i].angulo  = 0;
        obstacles[i].section = GAME_SECTION_SURFACE;
        obstacles[i].sprite  = al_load_bitmap("assets/images/bola.png");
    }

    /*Buraco*/
    obstacles[6].x = 3300; 
    obstacles[6].y = 762;
    obstacles[6].largura = 188; 
    obstacles[6].altura = 31;
    obstacles[6].tipo = BURACO; 
    obstacles[6].ativo = 0; 
    obstacles[6].grupo = 3;
    obstacles[6].vel_x = 0; 
    obstacles[6].vel_y = 0; 
    obstacles[6].angulo = 0;
    obstacles[6].section = GAME_SECTION_SURFACE;
    obstacles[6].sprite = al_load_bitmap("assets/images/buraco.png");

    /*Escada de saída (aparece ao entrar no subsolo)*/
    obstacles[7].x       = PLATFORM_LEFT;
    obstacles[7].y       = PLATFORM_Y + 20;
    obstacles[7].largura = 78;
    obstacles[7].altura  = GROUND_Y - (PLATFORM_Y + 20);
    obstacles[7].tipo    = ESCADA;
    obstacles[7].ativo   = 1;                   /*sempre pronta no subsolo*/
    obstacles[7].grupo   = 99;                  /*não faz parte do sistema de checkpoints*/
    obstacles[7].vel_x   = 0;
    obstacles[7].vel_y   = 0;
    obstacles[7].angulo  = 0;
    obstacles[7].section = GAME_SECTION_SUBSOLO;
    obstacles[7].sprite  = al_load_bitmap("assets/images/escada.png");

    /*Inimigo (ativado ao entrar no subsolo)*/
    obstacles[8].x       = 3100;                /*começa atrás do player (player cai em x≈3400)*/
    obstacles[8].y       = GROUND_Y - 170;
    obstacles[8].largura = 120;
    obstacles[8].altura  = 170;
    obstacles[8].tipo    = INIMIGO;
    obstacles[8].ativo   = 0;                   /*ativado pelo game.c ao entrar no subsolo*/
    obstacles[8].grupo   = 99;
    obstacles[8].vel_x   = 4;                   /*corre para a DIREITA*/
    obstacles[8].vel_y   = 0;
    obstacles[8].angulo  = 0;
    obstacles[8].section = GAME_SECTION_SUBSOLO;

    /*Faz a animação do inimigo*/
    for (int f = 0; f < 15; f++) {

        char path[64];
        snprintf(path, sizeof(path), "assets/images/Run (%d).png", f + 1);
        obstacles[8].run_frames[f] = al_load_bitmap(path);

    }

    /*Espinhos no chão (entre bolas e buraco)*/
    int espinho2_slots[] = {13, 14};
    int espinho2_x[]     = {2950, 3150};

    for (int e = 0; e < 2; e++) {
        int i = espinho2_slots[e];
        obstacles[i].x       = espinho2_x[e];
        obstacles[i].y       = GROUND_Y - 45;
        obstacles[i].largura = 70;
        obstacles[i].altura  = 45;
        obstacles[i].tipo    = ESPINHO;
        obstacles[i].ativo   = 0;
        obstacles[i].grupo   = 2;
        obstacles[i].vel_x   = 0;
        obstacles[i].vel_y   = 0;
        obstacles[i].angulo  = 0;
        obstacles[i].section = GAME_SECTION_SURFACE;
    }

    /*Morcegos voando (ativados ao entrar no subsolo, passam uma vez)*/
    int bat_slots[] = {15, 16, 19};
    int bat_x[]     = {3900, 4150, 4400};
    int bat_y[]     = {500, 540, 470};

    for (int b = 0; b < 3; b++) {
        int i = bat_slots[b];
        obstacles[i].x            = bat_x[b];
        obstacles[i].y            = bat_y[b];
        obstacles[i].largura      = 90;
        obstacles[i].altura       = 120;
        obstacles[i].tipo         = MORCEGO;
        obstacles[i].ativo        = 0;
        obstacles[i].grupo        = 99;
        obstacles[i].vel_x        = -5;
        obstacles[i].vel_y        = 0;
        obstacles[i].angulo       = 0;
        obstacles[i].section      = GAME_SECTION_SUBSOLO;
        obstacles[i].sprite_sheet = al_load_bitmap("assets/images/bat.png");
        
        if (obstacles[i].sprite_sheet)
            for (int f = 0; f < 4; f++)
                obstacles[i].run_frames[f] = al_create_sub_bitmap(obstacles[i].sprite_sheet, f * 32, 0, 32, 32);
    }

    /*Espinhos antes dos copos*/
    int espinho0_x[] = {800, 1050};

    for (int e = 0; e < 2; e++) {
        int i = 17 + e;
        obstacles[i].x       = espinho0_x[e];
        obstacles[i].y       = GROUND_Y - 45;
        obstacles[i].largura = 70;
        obstacles[i].altura  = 45;
        obstacles[i].tipo    = ESPINHO;
        obstacles[i].ativo   = 1;
        obstacles[i].grupo   = 0;
        obstacles[i].vel_x   = 0;
        obstacles[i].vel_y   = 0;
        obstacles[i].angulo  = 0;
        obstacles[i].section = GAME_SECTION_SURFACE;
    }

    /*Coração coletável (após os copos)*/
    obstacles[20].x       = 2000;
    obstacles[20].y       = GROUND_Y - 60;
    obstacles[20].largura = 50;
    obstacles[20].altura  = 50;
    obstacles[20].tipo    = CORACAO;
    obstacles[20].ativo   = 0;
    obstacles[20].grupo   = 1;
    obstacles[20].vel_x   = 0;
    obstacles[20].vel_y   = 0;
    obstacles[20].angulo  = 0;
    obstacles[20].section = GAME_SECTION_SURFACE;
    obstacles[20].sprite  = al_load_bitmap("assets/images/coracao.png");

    /*Coração coletável (subsolo)*/
    obstacles[21].x       = 3650;
    obstacles[21].y       = GROUND_Y - 60;
    obstacles[21].largura = 50;
    obstacles[21].altura  = 50;
    obstacles[21].tipo    = CORACAO;
    obstacles[21].ativo   = 0;
    obstacles[21].grupo   = 99;
    obstacles[21].vel_x   = 0;
    obstacles[21].vel_y   = 0;
    obstacles[21].angulo  = 0;
    obstacles[21].section = GAME_SECTION_SUBSOLO;
    obstacles[21].sprite  = al_load_bitmap("assets/images/coracao.png");

}


void update_obstacles(Obstacle *obstacles, int num_obstacles, int game_section, float camera_x) {

    /*Atualiza movimento e animação dos obstáculos ativos da seção atual */
    for (int i = 0; i < num_obstacles; i++) {

        if (!obstacles[i].ativo) 
            continue;
        if (obstacles[i].section != game_section) 
            continue;

        if (obstacles[i].tipo == PASSARO) {

            obstacles[i].x += obstacles[i].vel_x;

            if (obstacles[i].x < (int)camera_x - 200)
                obstacles[i].ativo = 0;

            obstacles[i].anim_timer++;

            if (obstacles[i].anim_timer >= 5) {

                obstacles[i].anim_timer = 0;
                obstacles[i].anim_frame = (obstacles[i].anim_frame + 1) % 3;

            }

        } else if (obstacles[i].tipo == BOLA) {

            obstacles[i].x      += obstacles[i].vel_x;
            obstacles[i].angulo += 0.08f;

            if (obstacles[i].x < 1500)
                obstacles[i].x = (int)obstacles[i].vel_y;

        } else if (obstacles[i].tipo == COPO) {

            obstacles[i].y += (int)obstacles[i].vel_y;

            if (obstacles[i].y > GROUND_Y)
                obstacles[i].y = -obstacles[i].altura;

        } else if (obstacles[i].tipo == INIMIGO) {

            obstacles[i].x += obstacles[i].vel_x;
            obstacles[i].anim_timer++;

            if (obstacles[i].anim_timer >= 5) {

                obstacles[i].anim_timer = 0;
                obstacles[i].anim_frame = (obstacles[i].anim_frame + 1) % 15;

            }

        } else if (obstacles[i].tipo == MORCEGO) {

            obstacles[i].x += obstacles[i].vel_x;

            if (obstacles[i].x < (int)camera_x - 200)
                obstacles[i].ativo = 0;

            obstacles[i].anim_timer++;

            if (obstacles[i].anim_timer >= 5) {

                obstacles[i].anim_timer = 0;
                obstacles[i].anim_frame = (obstacles[i].anim_frame + 1) % 4;

            }
        }
    }
}


void draw_obstacles(Obstacle *obstacles, int num_obstacles, float camera_x, int game_section) {

    for (int i = 0; i < num_obstacles; i++) {  /*varre todos e pula os inativados*/

        if (!obstacles[i].ativo) 
            continue;
        if (obstacles[i].section != game_section) 
            continue;

        float tela_x = obstacles[i].x - camera_x;

        if (obstacles[i].tipo == PASSARO) {

            ALLEGRO_BITMAP *frame = obstacles[i].run_frames[obstacles[i].anim_frame];
            if (!frame) continue;

            al_draw_scaled_bitmap(frame, 0, 0,al_get_bitmap_width(frame), al_get_bitmap_height(frame),tela_x, obstacles[i].y,obstacles[i].largura, obstacles[i].altura, 0);

        } else if (obstacles[i].tipo == INIMIGO) {

            ALLEGRO_BITMAP *frame = obstacles[i].run_frames[obstacles[i].anim_frame];
            if (!frame) continue;

            int flags = (obstacles[i].vel_x < 0) ? ALLEGRO_FLIP_HORIZONTAL : 0;

            al_draw_scaled_bitmap(frame, 0, 0,al_get_bitmap_width(frame), al_get_bitmap_height(frame),tela_x, obstacles[i].y,obstacles[i].largura, obstacles[i].altura, flags);

        } else if (obstacles[i].tipo == MORCEGO) {

            ALLEGRO_BITMAP *frame = obstacles[i].run_frames[obstacles[i].anim_frame];
            if (!frame) continue;

            al_draw_scaled_bitmap(frame, 0, 0,al_get_bitmap_width(frame), al_get_bitmap_height(frame),tela_x,
            (float)obstacles[i].y,obstacles[i].largura, obstacles[i].altura, 0);

        } else if (obstacles[i].tipo == CORACAO) {

            ALLEGRO_BITMAP *spr = obstacles[i].sprite;
            if (!spr) continue;

            al_draw_scaled_bitmap(spr, 0, 0,al_get_bitmap_width(spr), al_get_bitmap_height(spr),tela_x,
            obstacles[i].y,obstacles[i].largura, obstacles[i].altura, 0);

        } else if (obstacles[i].tipo == ESPINHO) {

            /*Desenha grupo de triângulos apontados pra cima*/
            float bx = tela_x;
            float by = (float)obstacles[i].y;
            float bh = (float)obstacles[i].altura;
            float bw = (float)obstacles[i].largura;
            float pw = bw / 4;

            ALLEGRO_COLOR c = al_map_rgb(180, 30, 30);

            for (int p = 0; p < 4; p++) {
                float x0 = bx + p * pw;
                float x1 = bx + (p + 1) * pw;
                al_draw_filled_triangle(x0, by + bh, (x0 + x1) / 2.0f, by, x1, by + bh, c);
            }

        } else if (obstacles[i].tipo == BOLA) {

            ALLEGRO_BITMAP *sprite = obstacles[i].sprite;
            if (!sprite) continue;

            float src_cx = al_get_bitmap_width(sprite)  / 2.0f;
            float src_cy = al_get_bitmap_height(sprite) / 2.0f;
            float dst_dx = tela_x + obstacles[i].largura / 2.0f;
            float dst_dy = obstacles[i].y + obstacles[i].altura / 2.0f;
            float xscale = (float)obstacles[i].largura / al_get_bitmap_width(sprite);
            float yscale = (float)obstacles[i].altura  / al_get_bitmap_height(sprite);

            al_draw_scaled_rotated_bitmap(sprite, src_cx, src_cy, dst_dx, dst_dy, xscale, yscale, obstacles[i].angulo, 0);

        } else {

            ALLEGRO_BITMAP *sprite = obstacles[i].sprite;

            if (sprite)
                al_draw_scaled_bitmap(sprite, 0, 0,al_get_bitmap_width(sprite), al_get_bitmap_height(sprite),tela_x, obstacles[i].y,obstacles[i].largura, obstacles[i].altura, 0);

        }
    }
}


void destroy_obstacles(Obstacle *obstacles, int num_obstacles) {

    for (int i = 0; i < num_obstacles; i++) {
        /*Sub-bitmaps antes do pai*/
        for (int f = 0; f < 15; f++) {

            if (obstacles[i].run_frames[f]) {

                al_destroy_bitmap(obstacles[i].run_frames[f]);
                obstacles[i].run_frames[f] = NULL;

            }
        }
        if (obstacles[i].sprite_sheet) {

            al_destroy_bitmap(obstacles[i].sprite_sheet);
            obstacles[i].sprite_sheet = NULL;

        }
        if (obstacles[i].sprite) {

            al_destroy_bitmap(obstacles[i].sprite);
            obstacles[i].sprite = NULL;
            
        }
    }
}
