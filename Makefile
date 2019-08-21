# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall 
LDFLAGS=-g

all: karger 

karger: graph.o

graph.o: graph.hpp vertex.hpp edge.hpp 

clean:
	rm -f karger *.o core* *~

