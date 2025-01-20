# Makefile for Limit Order Book

CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra -Wpedantic -Wshadow -arch arm64
LDFLAGS  = -g3 -arch arm64

# List of executables
EXECS    = tests Benchmark

# Object files needed for each executable
TEST_OBJS     = tests.o OrderBook.o Limit.o Order.o
BENCHMARK_OBJS = Benchmark.o OrderBook.o Limit.o Order.o

# Default target
all: clean ${EXECS}

# Targets for executables
tests: ${TEST_OBJS}
	${CXX} ${LDFLAGS} -o $@ $^

Benchmark: ${BENCHMARK_OBJS}
	${CXX} ${LDFLAGS} -o $@ $^

# Object file dependencies
OrderBook.o: OrderBook.cpp OrderBook.h
Limit.o: Limit.cpp Limit.h
Order.o: Order.cpp Order.h
tests.o: tests.cpp OrderBook.h Limit.h Order.h
Benchmark.o: Benchmark.cpp OrderBook.h Limit.h Order.h

# Generic rules for object files
%.o: %.cpp
	${CXX} ${CXXFLAGS} -c $<

# Clean target
clean:
	rm -rf ${EXECS} *.o *.dSYM

# Phony targets
.PHONY: all clean