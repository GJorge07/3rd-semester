#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>

/*definem estatísticas iniciais*/
#define PLAYER_SPEED      5     /*velocidade do player*/
#define JUMP_FORCE       -22    /*força do pulo*/ 
#define GRAVITY           1     /*gravidade*/
#define GROUND_Y        762     /*altura do chao  principal*/
#define PLATFORM_Y      420     /*altura do chão da plataforma elevada*/
#define PLATFORM_LEFT  4200     /*onde a plataforma começa (x da escada)*/
#define CLIMB_SPEED       4     /*velocidade de subida na escada*/
#define PLAYER_WIDTH     78     /*largura do player*/
#define PLAYER_HEIGHT   140     /*altura do player*/
#define PLAYER_CROUCH_H  70     /*altura quando agachado*/ 
#define PLAYER_LIFE       3     /*vida do player*/
#define WALK_FRAMES       6     /*frames da animação*/


/*Serve pra saber qual sprite desenhar, representa 0,1,2,3,4,5.
Como não serão alterados, não faz sentido fazer define como os outros*/
typedef enum {

    PLAYER_PARADO,
    PLAYER_ANDANDO,
    PLAYER_PULANDO,
    PLAYER_ABAIXADO,
    PLAYER_ESCALANDO

} PlayerEstado;

/*Guarda o estado atual de cada estatística*/
typedef struct {

    int x;
    int y;
    int largura;
    int altura;
    int vida;
    int on_ground;
    int on_platform;           
    int facing_left;          
    float vel_y;
    PlayerEstado estado;        /*parado, andando, pulando...*/
    int crouch_timer;           /*conta frames ao entrar no agachado*/
    int anim_frame;             /*qual frame*/
    int anim_timer;             /*conta frames*/
    ALLEGRO_BITMAP *sprite_sheet;   /*sprite original*/
    ALLEGRO_BITMAP *sprite_parado;
    ALLEGRO_BITMAP *sprite_abaixado;
    ALLEGRO_BITMAP *sprite_pulando;
    ALLEGRO_BITMAP *sprite_andando[WALK_FRAMES];
    ALLEGRO_BITMAP *sprite_andando_agachado[2];
    ALLEGRO_BITMAP *sprite_escalando[2];
    
} Player;


void init_player(Player *player, int x, int y);     /*Inicializa todos os campos do player com os valores iniciais e carrega os sprites:*/

void draw_player(Player *player, float camera_x);  /*Desenha o player no jogo*/
void update_player(Player *player, int move_left, int move_right, int agachado, int sobre_buraco, int escalando); /*att o estado do player*/

void jump_player(Player *player);                  /*Faz player pular*/
void destroy_player(Player *player);               /*Destroi player*/

#endif
