CC = gcc
CFLAGS = -Wall -pedantic -ggdb 
EXEC_NAME = ../bin/cos
LIBS = -lm # -lSDL
OBJ_FILES = main.o planete.o case_terrain_espace.o terrain_espace.o sauvegarde.o unite.o flotte.o terrain_combat.o case_terrain_combat.o jeu.o



#rajouter à la suite de cette liste les .o que l'on veut générer
#l'executable est générer dans le dossier bin/ sous le nom "main"

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC_NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ_FILES) $(EXEC_NAME)

