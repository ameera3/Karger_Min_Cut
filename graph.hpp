/*
 * Filename: Graph.hpp
 * Description: Implements a graph class for Karger's 
 *		min cut algorithm.
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include "vertex.hpp"
#include "edge.hpp"

using namespace std;

/* 
 * Class name: Graph
 * Instance Variables: vertex_map (unordered map of vertex names and
 *				   corresponding vertex pointers)
 *                     edges (vector of edge pointers)
 * Description: Implements a Graph class for Karger's 
 *              min cut algorithm                   
 * Public Methods: constructor, destructor, loadfromFile, Karger, find, merge
 * Private Methods: None                    
*/

class Graph {

public:

    // Unordered map of vertex labels and corresponding vertex pointers
    unordered_map<unsigned int,Vertex*> vertex_map;

    // Vector of Edge Pointers
    vector<Edge*> edges;

    /**
     * Constuctor of the graph
     */
    Graph(void);

    /*
     * Load the graph from its adjacency list representation.
     *
     * in_filename - input filename
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* filename);

    /* Destructor */
    ~Graph();

    /*
     * Karger's Algorithm
     * 
     * returns the size of the min cut
     */ 
    unsigned int Karger();

    /*
     * Finds the representative of the connected component that the vertex n
     * is in and implements path compression. Path compression makes all the
     * actors on a path from n to its parent, the direct children of the 
     * parent.
     *
     * n - Vertex* pointer representing n
     *
     * returns a Vertex* pointer pointing to the representative of
     * the connected component that the vertex n is in
     */ 

    Vertex* find( Vertex* n );

    /*
     * Merges the connected components that the vertices u and v are in 
     *
     * u -- Vertex* pointer 
     * v -- Vertex* pointer representing a vertex in a different
     *      connected component than u
     *
     * Possibly changes the parent of u or v and may also change the
     * rank of u or v.     
     *
     */ 
    void merge(Vertex* u, Vertex* v); 

    /*
     * Resets the ranks and parents of all the vertices
     */
    void reset();	

};


#endif // GRAPH_HPP
