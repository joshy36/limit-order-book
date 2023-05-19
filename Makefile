
# Makefile for Limit Order Book

CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
LDFLAGS  = -g3

tests: tests.o OrderBook.o Limit.o Order.o
	${CXX} -o $@ $^

OrderBook.o:     OrderBook.cpp OrderBook.h
Limit.o:		 Limit.cpp Limit.h
Order.o:		 Order.cpp Order.h

clean:
	rm -rf ${EXECS} *.o *.dSYM