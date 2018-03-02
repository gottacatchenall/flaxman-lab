
SRCS = 		src/tile/Tile.cc							\
					src/board/Board.cc						\
					src/envFactor/EnvFactor.cc		\
					src/individual/Individual.cc	\
					src/logger/Logger.cc					\
					src/util/cmd_line_opts.cc			\
					src/main.cc

DIRS = 		src/															\
					src/board/												\
					src/envFactor/										\
					src/individual/										\
					src/tile/													\
					src/logger												\
					src/util/

INC_PARAMS=$(foreach d, $(DIRS), -I$d)

CC = g++
CFLAGS = -std=c++11 -Wall -g $(INC_PARAMS)

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
