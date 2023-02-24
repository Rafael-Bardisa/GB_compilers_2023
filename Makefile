CC := cc

SRC := src
HDR := headers
OBJ := make
MAIN := apps

DEFINES := -DNO_FMT

SOURCES := $(wildcard $(SRC)/*.c)
HEADERS := $(wildcard $(HDR)/*.h)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

binaries/gb_project: $(OBJECTS) $(OBJ)/main.o
	$(CC) $(DEFINES) $^ -o $@

$(OBJ)/main.o: $(MAIN)/main.c $(MAIN)/main.h $(HEADERS)
	$(CC) $(DEFINES) -I$(HDR) -c $(MAIN)/main.c -o $(OBJ)/main.o

$(OBJ)/%.o: $(SRC)/%.c $(HDR)/*.h
	$(CC) $(DEFINES) -I$(SRC) -I$(HDR) -c $< -o $@

clean:
	echo $(RESOURCES)
	find . -type f -name '*.gch' -exec rm {} +

clone_resources:
	cp -r resources binaries

all: binaries/gb_project clone_resources
