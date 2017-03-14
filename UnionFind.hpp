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
using namespace std; //for cleaner/more readable code


/*
 * The class that represents node in the disjoint set
 */
class disjointNode {
    
public:
    disjointNode(Actor* actor) {
        this->actor=actor;
        up=NULL; //set to null initially, later on it would be null if it's
        //the sentinel node
        size=0;
    }
    ~disjointNode() {/*default destructor*/}
    
    
    
    //public setters and getters for better encapsulation
    void setUpNode(disjointNode* n) {
        
        this->up=n;
    }
    //getter that returns the parent node in the up-tree structure
    disjointNode* getUpNode() {
        return this->up;
    }
    
    //getter for the number of nodes that are connected to the calling node
    int getSize() {
        return this->size;
    }
    
    //set the number of nodes connected to the calling node
    void setSize(int n) {
        this->size=n;
    }
    
    //return/find the sentinel node
    disjointNode* getSentinel(){
        disjointNode* node=this;
        while(node->getUpNode()!=NULL&&node->getUpNode()!=node){
            node=node->getUpNode();
        }
        return node;
    }
    
    //get the actor pointer that is stored in the disjointNode
    Actor* getActor() {
        
        return this->actor;
    }
private:
    Actor* actor;
    disjointNode* up; //the parent node
    int size; //the number of nodes that point to this disjointNode
};



class UnionFind {
    
public:
    
    //the data structure that map the actor name to his/her parent node's name
    unordered_map<string, disjointNode*>* upTreeMap;
    
    //the constructor to construct a forest of single actor nodes
    UnionFind(ActorGraph* graph) {
        
        
        //initialize the up-tree map
        upTreeMap=new unordered_map<string, disjointNode*>();
        
        
        for(unordered_map<string, Actor*>::iterator it=graph->getActorList()->begin();
            it!=graph->getActorList()->end(); it++) {
            
            
            
            disjointNode* n=new disjointNode((*it).second);
            std::pair<string,disjointNode*> nodePair((*it).first, n);
            
            upTreeMap->insert(nodePair); //store the node pair in the hash map
        }
        
    }
    ~UnionFind(){  //destructor
        delete upTreeMap; //free up previously allocated memory
    }
    
    void unionUnite(disjointNode* n1, disjointNode* n2);
    
    
    
    
private:
    
    
    
};



/* The method that unites two sets, using union-by-size
 * Will only execute if two nodes are in different set
 */
void UnionFind:: unionUnite(disjointNode* n1, disjointNode* n2) {
    
    //first check if n1 and n2 are in the same set
    
    disjointNode* sentinel1=n1->getSentinel();
    disjointNode* sentinel2=n2->getSentinel();
    
    
    //if set1's size is smaller than(or equal to) set2, merge set1 to set2
    if(sentinel1->getSize()<=sentinel2->getSize()){
        //update the size of set 2
        sentinel2->setSize(sentinel1->getSize()+sentinel2->getSize()+1);
        sentinel1->setUpNode(sentinel2);
        
    }
    
    else {
        //merge set 2 to set 1, update the size of set 1
        sentinel1->setSize(sentinel2->getSize()+sentinel1->getSize()+1);
        
        sentinel2->setUpNode(sentinel1);
        
    }
    
    
}









