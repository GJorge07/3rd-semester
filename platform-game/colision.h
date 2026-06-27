#ifndef COLISION_H
#define COLISION_H

/*Função que determina a colisão ou não do player com algum dos obstáculos.
Se alguem tiver a esquerda, direita ou em cima do player, não colide, caso contrario, colide.
Parâmetros sao posição. largura e altura de obstaculo e player*/
int check_colision(int x1, int y1, int w1, int h1,int x2, int y2, int w2, int h2);


#endif