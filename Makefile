
SRCS = 				src/board/Board.cc				\
					src/tile/Tile.cc				\
					src/individual/Individual.cc	\
					src/genome/Genome.cc			\
					src/envFactor/EnvFactor.cc		\
					src/fragment/Fragment.cc		\
					src/fractal/Fractal.cc			\
					src/logger/Logger.cc			\
					src/random/Random.cc			\
					src/util/cmd_line_opts.cc		\
					src/main.cc

DIRS = 				src/							\
					src/board/						\
					src/tile/						\
					src/individual/					\
					src/genome/						\
					src/envFactor/					\
					src/fragment/					\
					src/fractal/					\
					src/logger						\
					src/random						\
					src/util/

INC_PARAMS=$(foreach d, $(DIRS), -I$d)

CC = g++
CFLAGS = -std=c++11 -Wall -g -march=native $(INC_PARAMS)

OBJS = $(SRCS:.c=.o)
EXE = mpfm

.PHONY: clean run

all:  $(EXE)
	@echo  Compiled successfully to $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(EXE)

run: $(EXE)
	./${EXE}
