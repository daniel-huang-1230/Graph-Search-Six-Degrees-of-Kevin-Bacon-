/*
 * ActorGraph.cpp
 * Author: Daniel Huang
 * Date:   2/28/2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include "ActorGraph.h"


using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {

    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
    
        // we have an actor/movie relationship, now what?
        
        Actor newActor=Actor(actor_name);

        if(actorList.find(&newActor)==actorList.end()) {
            //actor is not yet in the list, so add it
       
        this->actorList.insert(&newActor);
        }
        
        Movie newMovie=Movie(movie_title,movie_year);
        
        
        if(movieList.find(&newMovie)==movieList.end()) {
            //if movie is not yet in the list, add it to the moveList
            this->movieList.insert(&newMovie);
            newMovie.addToCast(&newActor); //add the actor name to the cast of the movie

        }
        else { //the movie is already added in the list previously,
               // then just go ahead and add the actor to its cast
            (*(movieList.find(&newMovie)))->addToCast(&newActor);
        }
        
    }
//at theis point, we should have all the actors and movies stores to our two sets
    
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
    
}




/** Build the graph with the information read from the file
 *  PRECONDITION: loadFromFile has been called
 */
void ActorGraph::buildGraph() {
    
    //iterate through every movie in the movieList and check their casts
    for(unordered_set<Movie*>::iterator it=movieList.begin(); it!=movieList.end(); it++){
        if((*it)->getCast().size()>1) {
            //if there are more than one actor in a movie, connect them all!
            for(int i=0; i<(*it)->getCast().size();i++) {
                for(int j=0; j<(*it)->getCast().size();j++){
                    if(j!=i) {
                        (*it)->getCast().at(i)->connect((*it)->getCast().at(j));
                    }
                }
            }
        
            
        }
    }
    
}


