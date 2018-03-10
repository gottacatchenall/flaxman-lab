
include ../../include.mk


INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

CC = g++
CFLAGS = -std=c++11 -Wall -g -march=native $(INC_PARAMS)

TEST_EXE = test/run_board_test
OBJS = $(SRCS:.c=.o) $(MAIN:.c=.o)


.PHONY: clean test

all:  test

test:
	$(CC) $(CFLAGS) -I$(MOCK_CLASS_DIR) $(MAIN_TEST) $(TEST_SRCS) $(GMOCK_LIB) $(GTEST_LIB) $(SRCS) -o $(TEST_EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(EXE)
