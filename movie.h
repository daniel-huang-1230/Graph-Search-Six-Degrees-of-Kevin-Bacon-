/*
 * Movie.h
 * Author: Daniel Huang
 * Date:   3/02/2017
 *
 *  This file defines a Movie class that represents the edges in the graph
 *
 */

#ifndef Movie_h
#define Movie_h
#include <vector>
#include <string>
#include "Actor.h"
using namespace std;

class Actor; //forward declaration
class Movie {
private:
    
    const int year;
    const string name;
    vector<Actor*>* cast; //the vector that stores all actor names appearing in the movie
    
public:
    //constructor (in-line initialization)
    Movie(string name,int year): year(year),name(name) {
        cast=new vector<Actor*>();
    }
    
    ~Movie() { delete cast; }
    
    //public getters
    string getName();
    
    int getYear();
    
    vector<Actor*>* getCast();
    
    //add the name of  actor to the cast
    void addToCast(Actor* actor);
    
    
};


#endif /* Movie_h */
