#include <stdio.h>
#include "map.h"
#include "player.h"
#include "game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *background_cave = NULL;

void init_map() {

    background = al_load_bitmap("assets/images/cenario.png");
    background_cave = al_load_bitmap("assets/images/cave.png");

}


void draw_map(float camera_x, int game_section) {

    if (game_section == GAME_SECTION_SURFACE) {

        /*Superfície: cenário da floresta*/
        if (background) {

            int offset = (int)(camera_x * 0.3f) % SCREEN_WIDTH;    /*faz o fundo "se mexer" */

            al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
            -offset,0, SCREEN_WIDTH, GROUND_Y, 0);

            al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
            -offset + SCREEN_WIDTH, 0, SCREEN_WIDTH, GROUND_Y, 0);

        }

        /*solo*/
        al_draw_filled_rectangle(0, GROUND_Y, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgb(30, 130, 30));

    } else {

        /*Subterrâneo: cenário da caverna */

        if (background_cave) {

            int offset = (int)(camera_x * 0.3f) % SCREEN_WIDTH;     /*faz o fundo "se mexer" */

            al_draw_scaled_bitmap(background_cave, 0, 0, al_get_bitmap_width(background_cave), al_get_bitmap_height(background_cave), -offset,0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

            al_draw_scaled_bitmap(background_cave, 0, 0, al_get_bitmap_width(background_cave), al_get_bitmap_height(background_cave), -offset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

        }

        /*Plataforma de saída (borda horizontal no topo da escada)*/

        float platform = PLATFORM_LEFT - camera_x;       /*calcula onde ela aparece na tela*/

        if (platform < SCREEN_WIDTH) {       /*verifica se está visível*/

            float draw_x = platform > 0 ? platform : 0;    /*evita desenhar fora da tela*/

            al_draw_filled_rectangle(draw_x, PLATFORM_Y, SCREEN_WIDTH, PLATFORM_Y + 20, al_map_rgb(139, 90, 43));

        }
    }
}


void destroy_map() {

    if (background) {

        al_destroy_bitmap(background);
        background = NULL;

    }

    if (background_cave) {

        al_destroy_bitmap(background_cave);
        background_cave = NULL;

    }

}
