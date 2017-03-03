//
//  Movie.cpp
//  PA4(Xcode project)
//
//  Created by Daniel Huang on 3/2/17.
//  Copyright © 2017 Daniel Huang. All rights reserved.
//


#include "Movie.h"



//public getters
string Movie::getName(){
    return this->name;
}


vector<string> Movie::getCast() {
    
    return this->cast;
}

//add the name of the actor to the cast
void Movie::addToCast(string actor_name) {
    this->getCast().push_back(actor_name);
    
    
}
