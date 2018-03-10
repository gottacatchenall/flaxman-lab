# ========================================
# Source
# ========================================

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

MAIN =              src/main.cc

SRCS = 				$(ROOT_DIR)/src/board/Board.cc				\
					$(ROOT_DIR)/src/patch/Patch.cc				\
					$(ROOT_DIR)/src/individual/Individual.cc	\
					$(ROOT_DIR)/src/genome/Genome.cc			\
					$(ROOT_DIR)/src/envFactor/EnvFactor.cc		\
					$(ROOT_DIR)/src/fragment/Fragment.cc		\
					$(ROOT_DIR)/src/fractal/Fractal.cc			\
					$(ROOT_DIR)/src/logger/Logger.cc			\
					$(ROOT_DIR)/src/random/Random.cc			\
					$(ROOT_DIR)/src/util/cmd_line_opts.cc

INCLUDE_DIRS = 		$(ROOT_DIR)/src/							\
					$(ROOT_DIR)/src/board/						\
					$(ROOT_DIR)/src/patch/						\
					$(ROOT_DIR)/src/individual/					\
					$(ROOT_DIR)/src/genome/						\
					$(ROOT_DIR)/src/envFactor/					\
					$(ROOT_DIR)/src/fragment/					\
					$(ROOT_DIR)/src/fractal/					\
					$(ROOT_DIR)/src/logger/						\
					$(ROOT_DIR)/src/random/						\
					$(ROOT_DIR)/src/util/

# ========================================
# Tests
# ========================================
TEST_MAIN =         $(ROOT_DIR)/test/main_test.cc
MOCK_CLASS_DIR = 	$(ROOT_DIR)/test/mock_classes
TEST_SRCS = 		$(ROOT_DIR)/test/main_test.cc								\
					$(ROOT_DIR)/src/board/test/board_test.cc 					\
					$(ROOT_DIR)/src/patch/test/test.cc							\
					$(ROOT_DIR)/src/individual/test/test.cc						\
					$(ROOT_DIR)/src/genome/test/test.cc							\
					$(ROOT_DIR)/src/envFactor/test/test.cc						\
					$(ROOT_DIR)/src/fragment/test/test.cc						\
					$(ROOT_DIR)/src/fractal/test/test.cc						\
					$(ROOT_DIR)/src/logger/test/test.cc							\
					$(ROOT_DIR)/src/random/test/test.cc							\
					$(ROOT_DIR)/src/util/test/test.cc

GTEST_LIB = /usr/local/lib/libgtest.a
GMOCK_LIB = /usr/local/lib/libgmock.a
