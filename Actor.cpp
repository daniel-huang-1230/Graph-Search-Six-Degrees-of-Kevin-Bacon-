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
/*vector<Actor* > Actor:: getAdj() {
    return this->adjList;
    
}
*/

//public getter for the member variable dist
int Actor:: getDist() {
    return this->dist;
}
//public setter to set the distance of actor
void Actor::setDist(int d){
    
    this->dist=d;
}


//public getter to get the previous node
/*Movie* Actor::getEdge(){
    return this->edge;
}*/

//public setter to set the previous node
/*void Actor::setEdge(Movie* m){
    this->edge=m;
 
}*/
//connect two actors if they co-starred in a movie
/*void Actor::connect(Actor* actor) {
    this->adjList.push_back(actor);
    
    //connect the two actors with an edge(movie)
   // this->setEdge(edge,0);
    //actor->setEdge(edge,0);
}*/

    
