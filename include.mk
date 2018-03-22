# ========================================
# Source
# ========================================

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

MAIN =              src/main.cc

SRCS = 				$(ROOT_DIR)/src/board/Board.cc					\
					$(ROOT_DIR)/src/patch/Patch.cc					\
					$(ROOT_DIR)/src/individual/Individual.cc		\
					$(ROOT_DIR)/src/genome/Genome.cc				\
					$(ROOT_DIR)/src/envFactor/EnvFactor.cc			\
					$(ROOT_DIR)/src/fragment/Fragment.cc			\
					$(ROOT_DIR)/src/fractal/Fractal.cc				\
					$(ROOT_DIR)/src/logger/Logger.cc				\
					$(ROOT_DIR)/src/random/Random.cc				\
					$(ROOT_DIR)/src/bio_functions/bio_functions.cc	\
					$(ROOT_DIR)/src/util/genetic_map.cc				\
					$(ROOT_DIR)/src/time_tracker/TimeTracker.cc		\
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
					$(ROOT_DIR)/src/bio_functions/				\
					$(ROOT_DIR)/src/time_tracker/				\
					$(ROOT_DIR)/src/util/

# ========================================
# Tests
# ========================================
TEST_MAIN =         $(ROOT_DIR)/test/main.cc
TEST_SRCS = 		$(ROOT_DIR)/test/tests.cc

GTEST_LIB = /usr/local/lib/libgtest.a
GMOCK_LIB = /usr/local/lib/libgmock.a
