#ifndef HUD_H
#define HUD_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "player.h"


void draw_carregando(ALLEGRO_FONT *f);  /*Desenha a palavra "CARREGANDO" antes de abrir o menu*/
void init_hud();                        /*Inicia ttf fonte e imagem do coração*/
void draw_hud(Player *player);      /*Desenha os corações no canto superior esquerdo da tela pra cada vida do player*/
void draw_menu();                       /*Desenha as linhas do menu*/
void draw_vitoria();                    /*Desenha a tela da vitória*/
void draw_derrota();                    /*Desenha tela da derrota*/
void draw_pausa();                      /*Desenha tela de pause*/
void destroy_hud();                      /*Destroi os desenhos*/

#endif
