#ifndef GAME_H
#define GAME_H

/*define caracteristicas gerais do jogo*/
#define LEVEL_WIDTH  5000
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define NUM_OBSTACULOS 22

/*define os possíveis estados do jogo*/
#define GAME_PLAYING 0
#define GAME_WON     1
#define GAME_LOST    2
#define GAME_MENU    3
#define GAME_PAUSED  4

#define GAME_SECTION_SURFACE 0   /*jogador na superfície*/
#define GAME_SECTION_SUBSOLO 1   /*jogador no subterrâneo*/


int init_game();        /*Inicia tudo que precisa pro jogo rodar*/
void game_loop();       /*Roda o jogo até ele ser fechado */
void game_destroy();    /*Libera tudo que foi alocado em init*/

#endif
