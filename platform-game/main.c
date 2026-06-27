#include "game.h"

/*Inicializa o jogo, faz o loop dele e o finaliza*/

int main() {

    if (!init_game())
        return 1;

    game_loop();
    game_destroy();
    
    return 0;

}
