/*
 * Filename: graph.cpp
 * Description: Implements a graph class for Karger's 
 *              min cut algorithm.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdlib.h> 
#include <time.h> 
#include "graph.hpp"

using namespace std;

/*
 * Constructor of the graph
 */ 
Graph::Graph(void) {}

/*
 * Load the graph from its adjacency list representation
 *
 * in_filename - input filename
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool Graph::loadFromFile(const char* filename) {
        
	// used to get each line from input file
        string line;

        // input file stream
        ifstream * in = new ifstream(filename);

	// Raise an error if file can't be read and return false
    	if (in->eof()) {
        	cerr << "Failed to read " << filename << "!\n";
        	return false;
    	}

        while (getline(*in, line)) {
                stringstream ss;
                // Storing the line into stringstream
                ss << line;

                // Running loop till the end of the stream
                string temp;
                unsigned int found = 0;
                unsigned int currentVertex;
                // extracting vertex number from stream;
                ss >> temp;
                if( stringstream(temp) >> currentVertex ){

			Vertex* vertex = new Vertex(currentVertex);
            		vertex->parent = vertex;
			vertex_map[currentVertex] = vertex;
                        while (!ss.eof()) {

                                // extracting word by word
                                ss >> temp;

                                /* Checking the given word is integer or not */
                                if ((stringstream(temp) >> found) 
					&& (found > currentVertex)){
                                        Edge* edge = new Edge(vertex_map[currentVertex], 
							vertex_map[found]);
					edges.push_back(edge);
                                }
                        }
                }
                ss.str("");
        }
        
	delete in;
	return true;
        
}

/*
 * Finds the representative of the connected component that the vertex n
 * is in and implements path compression. Path compression makes all the
 * vertices on a path from n to its parent, the direct children of the 
 * parent.
 *                          
 * n - Vertex* pointer representing vertex
 *                                    
 * returns a Vertex* pointer pointing to the representative of
 * the connected component that the vertex is in
 */

Vertex* Graph::find( Vertex* n ) { 

    if (n != n->parent) {
        n->parent = find(n->parent); 
    }                             
    return n->parent; 
} 

/*
 * Merges the connected components that the vertices u and v are in 
 *           
 * u -- Vertex* pointer representing a vertex
 * v -- Vertex* pointer representing a vertex in a different
 *      connected component than u
 *                               
 * Possibly changes the parent of u or v and may also change the
 * rank of u or v.     
 *                                              
 */

void Graph::merge(Vertex* u, Vertex* v) { 

    Vertex* uParent = find(u); 
    Vertex* vParent = find(v); 

    /* if two sets are unioned and have different ranks, the resulting set's 
     * rank is the larger of the two. Attach the shorter tree to the root of 
     * the taller tree. Thus, the resulting tree is no taller than the 
     * original trees.
     */  
    if (uParent->rank > vParent->rank) { 
        vParent->parent = uParent; 
    }    
    else { 
        uParent->parent = vParent; 
    }

    /* If two sets are unioned and have the same rank, the resulting set's 
     * rank is one larger; When we attach the tree to the other tree, the
     * resulting tree is taller by one node
     */  
    if (uParent->rank == vParent->rank) { 
        ++vParent->rank; 
    }
} 

 /*
  * Karger's Min-Cut Algorithm
  *            
  */

unsigned int Graph::Karger() {
	
	unsigned int V = vertex_map.size();
	unsigned int E = edges.size();
	unsigned int i;
	unsigned int cutEdges = 0;
	Vertex* compSource;
	Vertex* compDest;
	
	while( V >= 2 ){
		i = rand() % E;
		compSource = find((edges[i])->source);
		compDest = find((edges[i])->dest);
		if( compSource == compDest ){
			continue;
		}
		else{
			merge(compSource, compDest);
			--V;
		}	
  	}

	for(i = 0; i < edges.size(); ++i){
		compSource = find((edges[i])->source);
		compDest = find((edges[i])->dest);
		if( compSource != compDest ){
			++cutEdges;
		}
	}

	return cutEdges;
}    

/* 
 * Resets the ranks and parents of all the vertices
 */
void Graph::reset() {

	for( auto it = vertex_map.begin(); it != vertex_map.end(); ++it ){
		(it->second)->rank = 0;
		(it->second)->parent = it->second; 
	}
}

/*
 * Destructor: Iterate through the vertex map and delete all vertices
 *             Iterate through the edges vector and delete all edges.
 */

Graph::~Graph() {

    for ( auto it = vertex_map.begin(); it != vertex_map.end(); ++it ){
        delete it->second;
    }
    for ( unsigned int i = 0; i < edges.size(); ++i ){
        delete edges[i];
    }

}
