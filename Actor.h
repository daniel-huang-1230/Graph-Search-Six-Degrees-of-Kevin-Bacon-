/*
 * ActorGraph.h
 * Author: Daniel Huang
 * Date:   3/02/2017
 *
 *  This file defines an Actor class that essentially represents
 *  nodes in the graph
 */

#ifndef Actor_h
#define Actor_h
#include <vector>
#include <string>
#include "Movie.h"
using namespace std;


class Movie; //forward declaration
//the class of the node objects

class Actor {
    
private:
    const string name;
    
    int dist=-1 ; //the distance from the source vertex/node
    vector<Actor* > adjList; // the adjacency list to store "neighbors" on the graph
    
    pair <Movie*,Actor*> edge;  //the pointer that points to the edge(movie)
public:
    
    //constructor
    Actor(string name):name(name),edge(0,0){
        adjList=vector<Actor*>();
    }
    
    ~Actor() {} //default destructor
    
    bool operator==(const Actor& other) const{
        return (name==other.name);
    }
    //public getters
    string getName();
    
    vector<Actor* > getAdj();
    
    //public getter to get the distance of the actor node
    int getDist();
    //public setter to set the distance of the node
    void setDist(int d);
    
    
    //public getter to get the previous node
    pair <Movie*,Actor*> getEdge();
    
    //public setter to set the previous node
    
    void setEdge(Movie* m, Actor* a);
    
    //connect two actors if they co-starred in a movie
    void connect(Actor* actor);
    
};


#endif /* Actor_h */
