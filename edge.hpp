/*
 * Filename: edge.hpp
 * Description: Implements an edge class for a graph on
 *              which we will apply Karger's min cut algorithm.
 */

#ifndef EDGE_HPP
#define EDGE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Forward declaration of vertex class
 */
class Vertex;

/* 
 * Class name: Edge
 * Instance Variables: source (vertex pointer to source)
 *                     dest (vertex pointer to dest)
 *                     Although the edges are unordered, we
 *                     will store each edge with the vertex
 *                     with the lower valued label as the 
 *                     source and the higher valued label as
 *                     the destination.             
 * Description: Implements an edge class for a graph on which
 *              we will apply Karger's min cut algorithm.                  
 * Public Methods: constructor
 * Private Methods: None                    
*/

class Edge {

    public:

        // Source
        Vertex* source;

        // Destination
        Vertex* dest;

        // Constructor 
        Edge(Vertex* low, Vertex* high) :
            source(low), dest(high) {} 

};

#endif // EDGE_HPP
