# Variables:
CC=g++
BIN=./bin/main
INC=./inc/
SRC=./src/
OBJ=./obj/
#
# Flags d'erreurs:
ERROR_CFLAGS = -Wall -W
#
# Flags pour le compilateur:
GLIB_CFLAGS = $$(pkg-config --cflags glib-2.0)
PANGO_CFLAGS = $$(pkg-config --cflags pango)
GTK_CFLAGS := $$(pkg-config --cflags gtk+-2.0)
CFLAGS = $(ERROR_FLAGS) $(GLIB_CFLAGS)
#
# Flags pour l'editeur de liens:
GLIB_LDFLAGS = $$(pkg-config --libs glib-2.0)
PANGO_LDFLAGS = $$(pkg-config --libs pango)
GTK_LDFLAGS = $$(pkg-config --libs gtk+-2.0)
LDFLAGS = $(ERROR_FLAGS) $(GLIB_LDFLAGS) $(PANGO_LDFLAGS) $(GTK_LDFLAGS)
#
# Construction du programme:
all: $(BIN)
$(BIN): $(OBJ)main.o $(OBJ)Succ.o $(OBJ)Sommet.o $(OBJ)Graphe.o $(OBJ)Tas.o $(OBJ)Timer.o 
	$(CC) $(LDFLAGS) -o $(BIN) $(OBJ)main.o $(OBJ)Succ.o $(OBJ)Sommet.o $(OBJ)Graphe.o $(OBJ)Tas.o $(OBJ)Timer.o 
#
$(OBJ)Timer.o: $(SRC)Timer.cxx $(INC)Timer.h
	$(CC) -o $(OBJ)Timer.o -c $(SRC)Timer.cxx -Wall
#
$(OBJ)Tas.o: $(SRC)Tas.cxx $(INC)Tas.h
	$(CC) -o $(OBJ)Tas.o -c $(SRC)Tas.cxx -Wall
#
$(OBJ)Succ.o: $(SRC)Succ.cxx $(INC)Succ.h
	$(CC) -o $(OBJ)Succ.o -c $(SRC)Succ.cxx -Wall
#
$(OBJ)Sommet.o: $(SRC)Sommet.cxx $(INC)Sommet.h
	$(CC) -o $(OBJ)Sommet.o -c $(SRC)Sommet.cxx -Wall
#
$(OBJ)Graphe.o: $(SRC)Graphe.cxx $(INC)Graphe.h
	$(CC) -o $(OBJ)Graphe.o -c $(SRC)Graphe.cxx -Wall
#
$(OBJ)main.o: $(SRC)main.cxx $(INC)*
	$(CC) -o $(OBJ)main.o -c $(SRC)main.cxx -Wall
# Nettoyage:
#
clean:
	rm -rf $(OBJ)*.o
#
mrproper: clean
	rm -f *.o *~ core $(BIN)
