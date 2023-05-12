
# Makefile for Limit Order Book

CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
LDFLAGS  = -g3

main: main.o OrderBook.o
	${CXX} -o $@ $^

OrderBook.o:     OrderBook.cpp OrderBook.h

clean:
	rm -rf ${EXECS} *.o *.dSYM