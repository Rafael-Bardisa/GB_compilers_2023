CC := cc

SRC := src
HDR := headers
OBJ := make
MAIN := apps

SOURCES := $(wildcard $(SRC)/*.c)
HEADERS := $(wildcard $(HDR)/*.h)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

binaries/gb_project: $(OBJECTS) $(OBJ)/main.o
	$(CC) $^ -o $@

$(OBJ)/main.o: $(MAIN)/main.c $(MAIN)/main.h $(HEADERS)
	$(CC) -I$(HDR) -c $(MAIN)/main.c -o $(OBJ)/main.o

$(OBJ)/%.o: $(SRC)/%.c $(HDR)/*.h
	$(CC) -I$(SRC) -I$(HDR) -c $< -o $@

clean:
	find . -type f -name '*.gch' -exec rm {} +
