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
    
    int dist ; //the distance from the source vertex/node
   // vector<Actor* > adjList; // the adjacency list to store "neighbors" on the graph
    
    
    public:
    Actor* prev=0;
    vector<pair<Movie*,Actor*>> edges;

    //constructor
    Actor(string name):name(name){
        //adjList=vector<Actor*>();
        dist=-1;
        edges=vector<pair<Movie*,Actor*>>();
    }
    
    ~Actor() {} //default destructor
    
    bool operator==(const Actor& other) const{
        return (name==other.name);
    }
    //public getters
    string getName();
    
    //vector<Actor* > getAdj();
    
    //public getter to get the distance of the actor node
    int getDist();
    //public setter to set the distance of the node
    void setDist(int d);
    
    
    
    //vector<Movie*> getEdges();
    
    //public setter to set the previous node
    
    //void setEdge(Movie* m);
    
    //connect two actors if they co-starred in a movie
    void connect(Actor* actor);
    
};


#endif /* Actor_h */
