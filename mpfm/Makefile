CC = gcc
CFLAGS = -Wall

SRCS = 		src/Board/Board.cc			\
		src/EnvFactor/EnvFactor.cc		\
		src/Individual/Individual.cc		\
		src/main.cc

OBJS = $(SRCS:.c=.o)
EXE = mpfm

.PHONY: clean run warn

all:    $(EXE)
	@echo  Compiled successfully to $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXE) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(EXE)

run: all
	./${EXE}
