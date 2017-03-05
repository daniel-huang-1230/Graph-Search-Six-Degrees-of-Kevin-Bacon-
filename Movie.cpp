/*
 * Movie.cpp
 * Author: Daniel Huang
 * Date:   3/02/2017
 *
 *  This implementations of the Movie class
 *
 */

#include "Movie.h"



//public getters
string Movie::getName(){
    return this->name;
}


vector<Actor*>* Movie::getCast() {
    
    return this->cast;
}

//add the name of the actor to the cast
void Movie::addToCast(Actor* actor) {
    this->cast->push_back(actor);
    actor->setEdge(this, 0);
       
}
