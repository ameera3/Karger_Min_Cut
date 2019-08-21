# Karger_Min_Cut

## Usage
To compile, type "make". To run the program, type "./karger File" where File contains an adjacency list 
representation of a simple undirected graph.

## Introduction

The command line program karger.cpp takes in one parameter, an input file
name. The input file specified by the input file name should contain the
adjacency list representation of a simple undirected graph. The program
will output the minimum cut in the graph with high probability.

In order to output the minimum cut in the graph with high probability, the 
program implements [Karger's randomized min cut algorithm](https://en.wikipedia.org/wiki/Karger%27s_algorithm).
We use a [union-find data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure) to implement
the edge contraction efficiently.
