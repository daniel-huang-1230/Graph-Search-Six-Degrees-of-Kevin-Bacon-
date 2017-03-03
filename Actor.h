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
using namespace std;

//the class of the node objects
class Actor {
    
private:
    const string name;
    
    vector<Actor* > adjList; // the adjacency list to store "neighbors" on the graph
public:
    
    //constructor
    Actor(string name):name(name) {}
    
    ~Actor() {} //default destructor
    
    
    //public getters
    string getName();
    vector<Actor* > getAdj();
    
    //connect two actors if they co-starred in a movie
    void connect(Actor* actor);
    
};


#endif /* Actor_h */
