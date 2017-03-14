/*
 * Actor.h
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


//class Movie; //forward declaration
//the class of the node objects

class Actor{
    
private:
    const string name;
    
    int dist ; //the distance from the source vertex/node
   
    bool done;
    
    public:
    
    
    std::pair<Movie*,Actor*> prev;
    
    
    vector <pair<Movie*,Actor*>>* edges;

    //constructor
    Actor(string name):name(name){
        dist=-1;
        edges=new vector<pair<Movie*,Actor*>>();
    }
    
    ~Actor() {
        //delete edges;
    } //default destructor
    
    bool operator==(const Actor& other) const{
        return (name==other.name);
    }
    //public getters
    string getName();
    bool   isDone();
    
    //public getter to get the distance of the actor node
    int getDist();
    //public setter to set the distance of the node
    void setDist(int d);
    
    void setDone(bool isDone);
    
    void connect(Actor* actor);
    
};


#endif /* Actor_h */
