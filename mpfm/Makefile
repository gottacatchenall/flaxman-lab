COMPILER = g++
CPP_VERSION = c++11

# Output binary name
OUTPUT = mpfm
FLAGS =  -std=${CPP_VERSION}


HEADER = src/Board/Board.h		\
	 src/EnvFactor/EnvFactor.h	\
	 src/Individual/Individual.h	\
	 src/include.h

SRC = 	src/main.cc 			\
      	src/Board/Board.cc		\
	src/Individual/Individual.cc 	\
	src/EnvFactor/Envfactor.cc

# default target
all: main

main: $(HEADER)
	${COMPILER} ${FLAGS} ${SRC} -o ${OUTPUT}

clean:
	rm -f ${TARGET}.o
	rm ${OUTPUT}

# Run exec
run: clean all
	./${OUTPUT}


