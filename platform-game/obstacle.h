#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <allegro5/allegro.h>

/*Define os obstaculos do jogo*/
#define COPO      1
#define BOLA      2
#define BURACO    3
#define ESCADA    4
#define INIMIGO   6
#define PASSARO   7
#define MORCEGO   8
#define ESPINHO   9
#define CORACAO   10

/*define as caracteristicas dos obstaculos do jogo*/
typedef struct {

    int x;
    int y;
    int largura;
    int altura;
    int tipo;
    int ativo;
    int vel_x;
    float vel_y;
    float angulo;
    int grupo;
    int section;       /* 0 =superfície, 1 = subterrâneo*/
    int anim_frame;
    int anim_timer;
    
    ALLEGRO_BITMAP *sprite; /*imagem unica do obstaculo*/
    ALLEGRO_BITMAP *sprite_sheet;   /*imagem com varios frames */
    ALLEGRO_BITMAP *run_frames[15]; /*frames pra animação*/

} Obstacle;


void init_obstacles(Obstacle *obstacles, int num_obstacles);  /*inicia os obstaculos do jogo*/
void draw_obstacles(Obstacle *obstacles, int num_obstacles, float camera_x, int game_section); /*desenha obstaculos no jogo*/
void update_obstacles(Obstacle *obstacles, int num_obstacles, int game_section, float camera_x); /*atualiza estado dos obstaculos no jogo*/
void destroy_obstacles(Obstacle *obstacles, int num_obstacles); /*destroi obstaculos*/

#endif
