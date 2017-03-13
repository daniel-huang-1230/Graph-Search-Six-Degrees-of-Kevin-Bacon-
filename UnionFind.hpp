#include "ActorGraph.h"
#include <vector>
/*
 * UnionFind.hpp
 * Author: Daniel Huang
 * Date:   3/12/2017
 *
 * This file is implemented of the disjoint set ADT and would be used to answer
 * the query of actor connections
 */
using namespace std;
class UnionFind {
    
public:
    
    //the data structure that map the actor name to his/her parent node's name
    unordered_map<string, string>* upTreeMap;

    //the constructor to construct a forest of single actor nodes
    UnionFind(ActorGraph* graph) {
        
        
        //initialize the up-tree map and the size map
        upTreeMap=new unordered_map<string, string>();
        sizeMap=new unordered_map<string, int>();
        
        for(unordered_map<string, Actor*>::iterator it=graph->getActorList()->begin();
            it!=graph->getActorList()->end(); it++) {
            
            std::pair<string,string> nodePair((*it).first,"");
            
            upTreeMap->insert(nodePair); //store all the actors name, and they
            //are pointing to empty string initially
            
            std::pair<string,int> sizePair((*it).second->getName(),0);
            sizeMap->insert(sizePair); //map all nodes to their sizes
            
        }
        
    }
    ~UnionFind(){  //destructor
        delete upTreeMap; //free up previously allocated memory
    }
    
    void unionUnite(string* set1, string* set2);
    
    string* getSentinel(string* node);
    
    
    
private:
    
    //unordered_map<string, Actor*>* actorList;
    //unordered_map<string, Movie*>* movieList;
    unordered_map<string, int>* sizeMap; // keep track of size of the number of
    //nodes pointing to the key
    
    
    };


/* Find and return the sentinel(string) of the node in the up-tree
 */
string* UnionFind:: getSentinel(string* node) {
    unordered_map<string,string>::iterator it=upTreeMap->find(*node);
    string* sentinel=node;
    
    //use a vector to store nodes for path compression
    vector <pair<string,string>> temp=vector<pair<string,string>>();
    while((*it).second!="") {
        //traverse up until reaching the sentinel node
        it=upTreeMap->find((*it).second);
        
        //store the nodes found in the path for later compression
        temp.push_back((*it));
        
    }
    
    sentinel=(*it).first;
    
    //perform path compression
    for(int i=0; i<temp.size();i++){
        temp.at(i).second=sentinel;
        
    }

       return sentinel;
}

/* The method that unites two sets, using union-by-size
 */
void UnionFind:: unionUnite(string sentinel1, string sentinel2 ) {
    
    unordered_map<string,int>::iterator size1=sizeMap->find(sentinel1);
    unordered_map<string,int>::iterator size2=sizeMap->find(sentinel2);
    
    //if set1's size is smaller than(or equal to) set2, merge set1 to set2
    if((*size1).second<=(*size2).second) {
        //update the size of set2
        (*size2).second=(*size2).second+(*size1).second+1;
        unordered_map<string,string>::iterator it1=upTreeMap->find(sentinel1);
        
        //connect set1 to set2 (at the sentinel nodes)
        (*it1).second=sentinel2;
    }
    
    
    //merge set 2 to set1 otherwise
    else{
        //update the size of set1
        (*size1).second=(*size1).second+(*size2).second+1;
        unordered_map<string,string>::iterator it2=upTreeMap->find(sentinel2);
        //connect set2 to set1 (at the sentinel nodes)
        (*it2).second=sentinel1;
    }
    
    
}
