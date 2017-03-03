/*
 * ActorGraph.cpp
 * Author: Daniel Huang
 * Date:   3/02/2017
 *
 *  The impelementations for the Actor class
 *
 */

#include "Actor.h"



//public getter
string Actor:: getName() {
    return this->name;
    
}

//public getter that returns the adjacency list 
vector<Actor* > Actor:: getAdj() {
    return this->adjList;
    
}

//connect two actors if they co-starred in a movie
void Actor::connect(Actor* actor) {
    this->adjList.push_back(actor); //add another actor to their adjacency list
    
}
