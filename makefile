LIB=-lSDL -lSDL_image
Sokoban: main.o Sokoban.o
	gcc -o Sokoban main.o Sokoban.o $(LIB)

main.o: main.c
	gcc main.c $(LIB) -c 

Sokoban.o: Sokoban.c
	gcc Sokoban.c $(LIB) -c