CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
ALLEGRO = $(shell pkg-config --libs --cflags \
            allegro-5 \
            allegro_font-5 allegro_primitives-5 \
            allegro_image-5 allegro_ttf-5)

HDR = game.h player.h map.h obstacle.h colision.h hud.h
OBJ = main.o game.o player.o map.o obstacle.o colision.o hud.o

all: jogo

jogo: $(OBJ)
	$(CC) $(OBJ) -o jogo $(ALLEGRO)

main.o: main.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c main.c

game.o: game.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c game.c

player.o: player.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c player.c

map.o: map.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c map.c

obstacle.o: obstacle.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c obstacle.c

colision.o: colision.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c colision.c

hud.o: hud.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c hud.c

clean:
	rm -f *.o jogo
