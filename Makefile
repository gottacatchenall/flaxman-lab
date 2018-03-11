include include.mk

INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

EXE = mpfm
EXE_DEBUG = mpfm_debug
TEST_EXE = test/run_tests

CC = g++
CFLAGS = -std=c++11 -Wall -g -march=native $(INC_PARAMS)

DEBUG_FLAG = -D __DEBUG__

OBJS = $(SRCS:.c=.o) $(MAIN:.c=.o)

.PHONY: clean run test debug

all:  $(EXE)
	@echo  Compiled successfully to $(EXE)

debug: $(EXE_DEBUG)
	@echo Compiled successfully with __DEBUG__ flag to $(EXE)

$(EXE_DEBUG): $(OBJS)
	@echo Building mpfm with __DEBUG__ flag...
	@echo
	@$(CC) $(CFLAGS) $(DEBUG_FLAG) -o $(EXE) $(OBJS)

$(EXE): $(OBJS)
	@echo Building mpfm...
	@echo
	@$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

test:
	@echo Building tests from \$(MPFM_DIR)/test/tests.cc...
	@echo
	@$(CC) $(CFLAGS) $(TEST_SRCS) $(TEST_MAIN) $(GMOCK_LIB) $(GTEST_LIB) $(SRCS) -o $(TEST_EXE)

clean:
	$(RM) *.o *~ $(EXE)

run: $(EXE)
	./${EXE}
