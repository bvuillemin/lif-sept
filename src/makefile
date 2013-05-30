#Makefile du projet COS

.PHONY: clean, mrproper

CC = gcc
CFLAGS = -Wall -pedantic -ggdb 
EXEC_NAME = ../bin/cos
LIBPATH = #-L../lib
INCPATH = #-I../include
LIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx -lSDL_gfx -lfmodex
#SRC = $(wildcard *.c)
#OBJ_FILES = $(SRC:.c=.o)
OBJ_FILES = planete.o case_terrain_espace.o terrain_espace.o unite.o flotte.o terrain_combat.o case_terrain_combat.o jeu.o joueur.o batiment.o main.o affichage.o sauvegarde.o niveau.o animation.o vision.o son.o ia.o TableauDynamique.o #main.o 

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(LIBPATH) $(INCPATH) $(EXEC_NAME) $(LIBS)

%.o: %.c
	$(CC) $(INCPATH) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ_FILES)

mrproper: clean
	rm $(EXEC_NAME)

