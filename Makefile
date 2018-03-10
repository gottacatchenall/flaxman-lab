include include.mk

INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

EXE = mpfm
TEST_EXE = test/run_tests

CC = g++
CFLAGS = -std=c++11 -Wall -g -march=native $(INC_PARAMS)

OBJS = $(SRCS:.c=.o) $(MAIN:.c=.o)
.PHONY: clean run test

all:  $(EXE)
	@echo  Compiled successfully to $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

test:
	$(CC) $(CFLAGS) -I$(MOCK_CLASS_DIR) $(TEST_SRCS) $(GMOCK_LIB) $(GTEST_LIB) $(SRCS) -o $(TEST_EXE)

clean:
	$(RM) *.o *~ $(EXE)

run: $(EXE)
	./${EXE}
