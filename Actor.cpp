/*
 * Actor.cpp
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


//public getter for the member variable dist
int Actor:: getDist() {
    return this->dist;
}
//public setter to set the distance of actor
void Actor::setDist(int d){
    
    this->dist=d;
}




bool Actor:: isDone() {
    return this->done;
}


void Actor:: setDone(bool isDone){
    
    this->done=isDone;
}
