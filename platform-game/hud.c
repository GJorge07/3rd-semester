#include "hud.h"
#include "game.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

ALLEGRO_FONT   *font         = NULL;
ALLEGRO_BITMAP *heart_sprite = NULL;

void draw_carregando(ALLEGRO_FONT *f) {

    al_clear_to_color(al_map_rgb(0, 0, 0));    /*tela preta no fundo*/

    al_draw_text(
        f,
        al_map_rgb(200, 200, 200),
        SCREEN_WIDTH / 2,
        SCREEN_HEIGHT / 2,
        ALLEGRO_ALIGN_CENTER,
        "CARREGANDO..."
    );

    al_flip_display();
}


void init_hud() {

    font = al_load_ttf_font("/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf", 40, 0);  /*fonte do "carregando"*/

    heart_sprite = al_load_bitmap("assets/images/coracao.png");     /*imagem do coração */
}


void draw_hud(Player *player) {               /*Depende da vida do player*/

    if (!heart_sprite) 
        return;

    for (int i = 0; i < player->vida; i++) {
        al_draw_scaled_bitmap(heart_sprite,
            0, 0,
            al_get_bitmap_width(heart_sprite),
            al_get_bitmap_height(heart_sprite),
            31 + (i * 70), 31, 55, 55, 0);
    }
}


void draw_menu() {

    if (!font) 
        return;

    al_draw_text(font, al_map_rgb(255, 255, 255),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60,
        ALLEGRO_ALIGN_CENTER, "INICIAR CORRIDA - ENTER");

    al_draw_text(font, al_map_rgb(200, 200, 200),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20,
        ALLEGRO_ALIGN_CENTER, "SAIR - ESC");

    al_draw_text(font, al_map_rgb(150, 150, 150),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 90,
        ALLEGRO_ALIGN_CENTER, "MOVER: A/D  PULAR: ESPACO  AGACHAR: S  ESCALAR: W");
}


void draw_vitoria() {

    if (!font) 
        return;

    al_draw_text(font, al_map_rgb(50, 255, 50),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40,
        ALLEGRO_ALIGN_CENTER, "VOCE GANHOU!");

    al_draw_text(font, al_map_rgb(200, 200, 200),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40,
        ALLEGRO_ALIGN_CENTER, "ENTER para jogar de novo  ESC para sair");
}


void draw_derrota() {

    if (!font) 
        return;

    al_draw_text(font, al_map_rgb(255, 50, 50),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40,
        ALLEGRO_ALIGN_CENTER, "VOCE PERDEU!");

    al_draw_text(font, al_map_rgb(200, 200, 200),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40,
        ALLEGRO_ALIGN_CENTER, "ENTER para jogar de novo  ESC para sair");
}


void draw_pausa() {

    if (!font) 
        return;

    al_draw_text(font, al_map_rgb(255, 255, 100),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60,
        ALLEGRO_ALIGN_CENTER, "PAUSADO");

    al_draw_text(font, al_map_rgb(255, 255, 255),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20,
        ALLEGRO_ALIGN_CENTER, "VOLTAR A CORRER - ENTER");

    al_draw_text(font, al_map_rgb(200, 200, 200),
        SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80,
        ALLEGRO_ALIGN_CENTER, "DESISTIR DA CORRIDA - ESC");
}


void destroy_hud() {

    if (font) {

        al_destroy_font(font);
        font = NULL;

    }

    if (heart_sprite) {

        al_destroy_bitmap(heart_sprite);
        heart_sprite = NULL;

    }
}
