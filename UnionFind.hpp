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


/*
 * The class that represents node in the disjoint set
 */
class disjointNode {
    
public:
    disjointNode(Actor* actor) {
        this->actor=actor;
        up=NULL;
        sentinel=true;//every node IS sentinel node initially
        size=0;
    }
    ~disjointNode() {/*default destructor*/}
    
    
    void setSentinel(bool isSentinel){
        this->sentinel=isSentinel;
    }
    
    bool isSentinel() {
        return this->sentinel;
    }
    void setUpNode(disjointNode* n) {
        
        this->up=n;
    }
    disjointNode* getUpNode() {
        return this->up;
    }
    
    int getSize() {
       return this->size;
    }
    
    void setSize(int n) {
        this->size=n;
    }
    
    disjointNode* getSentinel(){
        disjointNode* node=this;
        while(node->getUpNode()!=NULL&&node->getUpNode()!=node){
            node=node->getUpNode();
        }
        return node;
    }
    
    Actor* getActor() {
        
        return this->actor;
    }
private:
    Actor* actor;
    disjointNode* up; //the parent node
    bool sentinel;
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
       
        //sizeMap=new unordered_map<string, int>();
        
        for(unordered_map<string, Actor*>::iterator it=graph->getActorList()->begin();
            it!=graph->getActorList()->end(); it++) {
            
            
            /*std::pair<string,string*> nodePair((*it).first,NULL);
            
            //for single node, make the pointer point to itself initially
            nodePair.second=&nodePair.first;
            upTreeMap->insert(nodePair); //store all the actors name, and they
            //are pointing to empty string initially
            
            std::pair<string,int> sizePair((*it).second->getName(),0);
            sizeMap->insert(sizePair); //map all nodes to their sizes*/
            
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
    
    
    //unordered_map<string, int>* sizeMap; // keep track of size of the number of
    //nodes pointing to the key
    
    
    };


/* Find and return the sentinel(string) of the node in the up-tree
 */
/*string UnionFind:: getSentinel(string node) {
    unordered_map<string,string*>::iterator it=upTreeMap->find(node);
    string sentinel=node;
    
    //use a vector to store nodes for path compression
    vector <pair<string,string*>> temp=vector<pair<string,string*>>();
    while(*(*it).second!=(*it).first) {
        //traverse up until reaching the sentinel node
        it=upTreeMap->find(*(*it).second);
        
        //store the nodes found in the path for later compression
        temp.push_back((*it));
        
    }
    
    sentinel=(*it).first;
    
    //perform path compression
    for(int i=0; i<temp.size();i++){
        *(temp.at(i).second)=(*it).first;
        
    }

       return sentinel;
}*/

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
            sentinel1->setSentinel(false); //sentinel 1 is no longer a sentinel node
        }
        
        else {
            //merge set 2 to set 1, update the size of set 1
            sentinel1->setSize(sentinel2->getSize()+sentinel1->getSize()+1);
            
            sentinel2->setUpNode(sentinel1);
            sentinel2->setSentinel(false);
        }
    
        
        
    
}









/*void UnionFind:: unionUnite(string* sentinel1, string* sentinel2 ) {
    
    unordered_map<string,int>::iterator size1=sizeMap->find(*sentinel1);
    unordered_map<string,int>::iterator size2=sizeMap->find(*sentinel2);
    
    //if set1's size is smaller than(or equal to) set2, merge set1 to set2
    if((*size1).second<=(*size2).second) {
        //update the size of set2
        (*size2).second=(*size2).second+(*size1).second+1;
        unordered_map<string,string*>::iterator it1=upTreeMap->find(*sentinel1);
        
        //connect set1 to set2 (at the sentinel nodes)
        (*it1).second=sentinel2;
    }
    
    
    //merge set 2 to set1 otherwise
    else{
        //update the size of set1
        (*size1).second=(*size1).second+(*size2).second+1;
        unordered_map<string,string*>::iterator it2=upTreeMap->find(*sentinel2);
        //connect set2 to set1 (at the sentinel nodes)
        (*it2).second=sentinel1;
    }
    
    
}*/





