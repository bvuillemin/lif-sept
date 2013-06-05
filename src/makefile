#Makefile du projet COS

.PHONY: clean, mrproper

CC = gcc
CFLAGS = -Wall -pedantic -ggdb 
EXEC_NAME = ../bin/cos
TEST_NAME = ../bin/test
LIBPATH = 
INCPATH = 
LIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx -lSDL_gfx -lfmodex -L../lib/lib

OBJ_FILES = planete.o case_terrain_espace.o terrain_espace.o unite.o flotte.o terrain_combat.o case_terrain_combat.o jeu.o joueur.o batiment.o affichage.o sauvegarde.o animation.o vision.o son.o ia.o TableauDynamique.o 
MAIN_FILE = main.o
MAIN_TEST_FILE = main_test.o

all: $(EXEC_NAME) $(TEST_NAME)

$(EXEC_NAME):  $(MAIN_FILE) $(OBJ_FILES)
	$(CC)  $(MAIN_FILE) $(OBJ_FILES) -o $(LIBPATH) $(INCPATH) $(EXEC_NAME) $(LIBS)

$(TEST_NAME): $(MAIN_TEST_FILE) $(OBJ_FILES)
	$(CC) $(MAIN_TEST_FILE) $(OBJ_FILES) -o $(LIBPATH) $(INCPATH) $(TEST_NAME) $(LIBS)

%.o: %.c
	$(CC) $(INCPATH) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ_FILES)

mrproper: clean
	rm $(EXEC_NAME)

