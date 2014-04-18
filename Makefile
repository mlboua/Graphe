CC=gcc -g
CFLAGS=-O4 -W -Wall
CPPFLAG=-I
LDLIBS=-lGraphe -lm
	

SRC = ./src
OBJ = ./obj
BIN = ./bin
LIB = ./lib
INC = ./include

MAIN = $(BIN)/main

all:$(OBJ) $(BIN) $(LIB) $(MAIN)

$(MAIN) : $(SRC)/main.c $(OBJ)/menu.o $(LIB)/libgraphe.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -L$(LIB) $(LDLIBS) 

$(OBJ)/%.o : $(SRC)/%.c $(INC)/%.h $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(OBJ)/$*.o

$(LIB)/libgraphe.a : $(OBJ)/libGraphe.o $(OBJ)/libListe.o
	ar rc $@  $(OBJ)/libGraphe.o $(OBJ)/libListe.o
	ranlib $@

	ar -rv ./lib/libListe.a ./obj/libListe.o

$(OBJ) : 
	mkdir $(OBJ)

$(BIN) : 
	mkdir $(BIN)

$(LIB) : 
	mkdir $(LIB)

clean : 
	rm $(OBJ); rm *~
