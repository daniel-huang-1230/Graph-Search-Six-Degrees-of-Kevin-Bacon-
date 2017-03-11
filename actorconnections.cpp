/*
 * actorconnection.cpp
 * Author: Daniel Huang
 * Date:   3/10/2017
 *
 * This file is implemented to answer the following query: for every actor pair 
 (X, Y) in the given list: "After which year did actors X and Y become connected?"
 */
#include "ActorGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std; //for cleaner looking code
//actorconnections will take 4 command line arguments
int main(int argc, char* argv[]) {
    
    //check the number of arguments
    if(argc!=5) {
        cout<<"Invalid number of arguments."
            <<" Must be 4 command-line argument."<<endl;
        return -1;
    }
    
    ActorGraph graph= ActorGraph(); //initialize the graph object
    
    //first load all the actors and movies to their lists, respectively
    
    graph.loadFromFile(argv[1], false);
    
    //extract the earliest&lastest movie years in the input cast file
    int earliestYear=numeric_limits<int>::max(); //initialize it to infinity
    
    int latestYear=0; //initialize the latest year to 0 first
    for(unordered_map<string, Movie*>::iterator it=graph.getMovieList()->begin();it!=graph.getMovieList()->end();it++)
    {
        if((*it).second->getYear()<earliestYear){
            earliestYear=(*it).second->getYear(); //update the earliest year
           
        }
        if((*it).second->getYear()>latestYear) {
            latestYear=(*it).second->getYear(); //update the lastest year
        }
    }
    
    
    //for debugging purpose
     cout<<"the earliest year in the file is "<<earliestYear<<endl;
     cout<<"the lastest year in the file is "<<latestYear<<endl;
    
    
    //initialize a vector container to hold all pairs of actor in the query 
    vector<pair<string, int>>* pairContainer;
    //loop through each year in the possible year range
    for(int yr=earliestYear; yr<=latestYear; yr++) {
        
        graph.buildGraph(yr); //build the edges until year yr
        
        //check for paths for all pairs of actors
        
        
    }
    
    
    
    
    return 0; //exit normally
}
