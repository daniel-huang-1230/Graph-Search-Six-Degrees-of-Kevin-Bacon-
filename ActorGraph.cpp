/*
 * ActorGraph.cpp
 * Author: Daniel Huang
 * Date:   3/02/2017
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

ActorGraph::ActorGraph() {
    //this->actorList=new  unordered_map<string,Actor*>();
    //this->movieList=new unordered_map<string,Movie*>();
}

//public getter
unordered_map<string,Actor>* ActorGraph:: getActorList() {
    return this->actorList;
}

//public getter
unordered_map<string,Movie*>* ActorGraph:: getMovieList() {
    return this->movieList;
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    //TODO: use_weighted_edges not yet implemented!!!
    
    
    // Initialize the file stream
    ifstream infile;
    infile.open(in_filename);
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
        
        if(actorList->find(actor_name)==actorList->end()) {
            //actor is not yet in the list, so add it
            
            pair<string,Actor> actorPair (newActor.getName(), newActor);
            this->actorList->insert(actorPair);
                   }
        
        Movie newMovie=Movie(movie_title,movie_year);
        //Concatenate the name and year of the movie for comparison
        string namePlusYear=newMovie.getName()+"#@"+to_string(movie_year);
        
        
        
        
        if(movieList->find(namePlusYear)==movieList->end()) {
            //if movie is not yet in the list, add it to the movieList
            
            pair<string,Movie*> moviePair (namePlusYear,&newMovie);
            this->movieList->insert(moviePair);
            
            
            unordered_map<string,Movie*>::iterator it=this->getMovieList()->find(namePlusYear);
            (*it).second->addToCast(&newActor); //add the actor to the cast of the movie
            
        }
        else { //the movie is already added in the list previously,
            // then just go ahead and add the actor to its cast
            unordered_map<string,Movie*>::iterator it=this->getMovieList()->find(namePlusYear);
            (*it).second->addToCast(&newActor);
           

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
 *  POSTCONDITION: A graph representation of movies and actors is built
 */
void ActorGraph::buildGraph() {
    
    //iterate through every movie in the movieList and check their casts
    for(unordered_map<string,Movie*>::iterator it=this->getMovieList()->begin(); it!=this->getMovieList()->end(); it++){
        if((*it).second->getCast()->size()>1) {
            //if there are more than one actor in a movie, connect them all!
            for(int i=0; i<(*it).second->getCast()->size();i++) {
                for(int j=0; j<(*it).second->getCast()->size();j++){
                    if(j!=i) {
                        
                        //SEGFAULT!!!!!!!!
                        
                        (*it).second->getCast()->at(i)->connect((*it).second->getCast()->at(j));
                    }
                }
            }
            
            
        }
    }
    
}


/** The bread-first search algorithm that would traverse the graph and find the
 *  shortest path from the start actor s
 */
void ActorGraph::BFS(Actor* s) {
    queue<Actor*> queue; //initialize the queue to store actor nodes
    queue.push(s);
    Actor* curr;
    s->setDist(0);
    while(!queue.empty()) {
        //curr=queue.front(); //set the curr node
        queue.pop();
        for(int i=0; curr->getAdj().size();i++) {
            //for each of curr's neighbors, n
            if(curr->getAdj().at(i)->getDist()==-1){
                curr->getAdj().at(i)->setDist(curr->getDist()+1);
                
                curr->getAdj().at(i)->setEdge( curr->getAdj().at(i)->getEdge().first,curr);
                queue.push(curr->getAdj().at(i)); //enqueue n
            }
        }
    }
    //at this point we have finished the search and done exploring from S
}


Actor ActorGraph::findActor(string key) {
    unordered_map<string,Actor>::iterator it=this->getActorList()->find(key);
    
    return (*it).second;
}

ActorGraph::~ActorGraph() {
    delete movieList;
    delete actorList;
}

