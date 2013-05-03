CC = gcc
CFLAGS = -Wall -pedantic -ggdb 
EXEC_NAME = ../bin/cos
LIBS = -lm -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx
#-lSDL_rotozoom -lSDL_framerate
OBJ_FILES = planete.o case_terrain_espace.o terrain_espace.o unite.o flotte.o terrain_combat.o case_terrain_combat.o jeu.o joueur.o batiment.o main2.o affichage.o sauvegarde.o#  main.o 



#rajouter à la suite de cette liste les .o que l'on veut générer
#l'executable est générer dans le dossier bin/ sous le nom "main"

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC_NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ_FILES) $(EXEC_NAME)

