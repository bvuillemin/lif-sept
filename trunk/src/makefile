CC = gcc
CFLAGS = -Wall -pedantic -ggdb 
EXEC_NAME = ../bin/main
LIBS = # -lSDL
OBJ_FILES = main.o planete.o case.o terrain.o niveau.o unite.o flotte.o



#rajouter à la suite de cette liste les .o que l'on veut générer
#l'executable est générer dans le dossier bin/ sous le nom "main"

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC_NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJ_FILES)

