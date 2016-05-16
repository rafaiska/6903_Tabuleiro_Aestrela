DIRINCLUDE=./include
DIROBJETO=./obj
CC=g++
CFLAGS=-I$(DIRINCLUDE)

_DEPEND = tabuleiro.h
DEPEND = $(patsubst %,$(DIRINCLUDE)/%,$(_DEPEND))

_OBJETO = tabuleiro.o main.o
OBJETO = $(patsubst %,$(DIROBJETO)/%,$(_OBJETO))

$(DIROBJETO)/%.o: %.cpp $(DEPEND)
	$(CC) -c -o $@ $< $(CFLAGS)

astar_tabuleiro.out: $(OBJETO)
	$(CC) -o ./bin/$@ $^ $(CFLAGS)
