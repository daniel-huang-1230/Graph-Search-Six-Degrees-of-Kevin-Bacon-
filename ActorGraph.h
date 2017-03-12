/*
 * ActorGraph.h
 * Author: Daniel Huang
 * Date:   2/28/2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include "Actor.h"
#include "Movie.h"

#include <unordered_map>
#include <queue>
//#include <priority_queue>
// Maybe include some data structures here

using namespace std;

class ActorGraph {
protected:
    // Maybe add class data structure(s) here
    
//use unordered_set to achieve fast search and retrieval
    unordered_map<string, Actor*>* actorList=new  unordered_map<string,Actor*>();
    unordered_map<string, Movie*>* movieList=new unordered_map<string, Movie*>();

public:
    ActorGraph();
    ~ActorGraph();
    
    bool weighted; //indicate if the path is calculated in the weighted manner or not
    
    unordered_map<string,Actor* >* getActorList();
    
    unordered_map<string, Movie* >* getMovieList();
    
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
    
    
    /** Build the graph with the information read from the file
     *  PRECONDITION: loadFromFile has been called 
     */
    void buildGraph();
    
    /** Build the graph by connecting all edges between actors after(including) 
     *  a certain year.
     *  PRECONDITION: loadFromFile has been called
     */
    void buildGraph(int year);
    
    /** The bread-first search algorithm that woul find the shortest path from the 
     * start actor s
     */
    void BFS(Actor* s, Actor* e);
    
    /** Dijkstra's algorithm to find the lowest cost path
     */
    void Dij(Actor*from);
};


#endif // ACTORGRAPH_H
