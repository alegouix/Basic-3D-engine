CC=gcc
CFLAGS=-g -Wall -Werror
LD=-lSDL2 -lSDL2main -lm
BINPATH=bin
SRCPATH=src

build: $(BINPATH) $(BINPATH)/engine

run:
	make build
	./$(BINPATH)/engine

$(BINPATH):
	mkdir $(BINPATH)

$(BINPATH)/engine: $(BINPATH)/main.o
	$(CC) $(BINPATH)/*.o -o $(BINPATH)/engine ${LD}

$(BINPATH)/main.o: $(SRCPATH)/main.* $(BINPATH)/engine.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/main.c -o $(BINPATH)/main.o

$(BINPATH)/engine.o: $(BINPATH)/point.o $(BINPATH)/draw.o $(BINPATH)/engine_defs.o $(BINPATH)/model.o $(BINPATH)/triangle.o
	

$(BINPATH)/point.o: $(SRCPATH)/point.* $(BINPATH)/vector.o $(BINPATH)/engine_defs.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/point.c -o $(BINPATH)/point.o

$(BINPATH)/draw.o: $(SRCPATH)/draw.*  $(BINPATH)/triangle.o $(BINPATH)/point.o $(BINPATH)/utils.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/draw.c -o $(BINPATH)/draw.o

$(BINPATH)/triangle.o: $(SRCPATH)/triangle.* $(BINPATH)/point.o $(BINPATH)/vector.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/triangle.c -o $(BINPATH)/triangle.o

$(BINPATH)/model.o: $(SRCPATH)/model.* $(BINPATH)/point.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/model.c -o $(BINPATH)/model.o

$(BINPATH)/engine_defs.o: $(SRCPATH)/engine_defs.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/engine_defs.c -o $(BINPATH)/engine_defs.o

$(BINPATH)/utils.o: $(SRCPATH)/utils.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/utils.c -o $(BINPATH)/utils.o


$(BINPATH)/vector.o: $(SRCPATH)/vector.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/vector.c -o $(BINPATH)/vector.o

clean:
	rm -r $(BINPATH)