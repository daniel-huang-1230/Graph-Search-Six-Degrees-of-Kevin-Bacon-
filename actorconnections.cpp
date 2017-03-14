/*
 * actorconnection.cpp
 * Author: Daniel Huang
 * Date:   3/10/2017
 *
 * This file is implemented to answer the following query: for every actor pair
 (X, Y) in the given list: "After which year did actors X and Y become connected?"
 *
 */
#include "ActorGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "UnionFind.hpp"
using namespace std; //for cleaner looking code
long BILLION=1000000000; //to convert nanosecond to second

//actorconnections will take 4 command line arguments
int main(int argc, char* argv[]) {
    
    //check the number of arguments
    if(argc<4) {
        cout<<"Invalid number of arguments."
        <<" Must be at least 3 command-line arguments."<<endl;
        return -1;
    }
    
    ActorGraph graph= ActorGraph(); //initialize the graph object
    
    //first load all the actors and movies to their lists, respectively
    
    graph.loadFromFile(argv[1], false);
    
    //extract the earliest&lastest movie years in the input cast file
    int earliestYear=numeric_limits<int>::max(); //initialize it to infinity
    
    int latestYear=0; //initialize the latest year to 0 first
    for(unordered_map<string, Movie*>::iterator it=graph.getMovieList()->begin();
        it!=graph.getMovieList()->end();it++)
    {
        if((*it).second->getYear()<earliestYear){
            earliestYear=(*it).second->getYear(); //update the earliest year
            
        }
        if((*it).second->getYear()>latestYear) {
            latestYear=(*it).second->getYear(); //update the lastest year
        }
    }
    
    
    //initialize a vector container to hold all pairs of actor nodes in the query file
    vector< pair<Actor*, Actor*> >* pairContainer=new vector< pair<Actor*, Actor*> >();
    
    
    ifstream infile;  //open the test_pairs file
    infile.open(argv[2]);
    
    bool have_header = false; //used for skipping the header line
    
    string name1;
    string name2;
    while(infile) {
        
        
        string s;
        // get the next line
        if (!getline( infile, s )) break;
        
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        
        istringstream ss( s );
        vector <string> record; //a temporary holder to store pair
        string name1;
        string name2;
        while (ss) {
            string next;
            
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;
            record.push_back( next );
        }
        
        if (record.size() != 2) {
            // we should have exactly 2 columns, representing two actors/actresses
            continue;
        }
        name1=string(record[0]);
        name2=string(record[1]);
        unordered_map<string, Actor*>::iterator it1=graph.getActorList()->find(record[0]);
        unordered_map<string, Actor*>::iterator it2=graph.getActorList()->find(record[1]);
        
        
        
        std::pair<Actor*,Actor*> actorPair((*it1).second,(*it2).second);
        pairContainer->push_back(actorPair); //store the actor pair
    }
    //at this point, all actor pairs should be stored in place
    
    
    
    ofstream outfile(argv[3]); //initialize the output file stream
    
    Timer timer; //create a timer object
    
    ///////////////////////////////////using the BFS start////////////////////////
    
    if(argv[4]!=NULL&&string(argv[4])=="bfs") {
        
        timer.begin_timer(); //start the timer
        //initialize anther vector container to store all name pairs that are connected
        vector<string>* namePair=new vector<string>();
        
        
        //the container that holds the actual connected pairs of actors
        unordered_map<string,int>* connectedPair=new unordered_map<string,int>();
        
        //loop through each year in the possible year range
        for(int yr=earliestYear; yr<=latestYear; yr++) {
            bool yearPresent=false;
            //only build the graph when there were movies in the certain year
            for(unordered_map<string,Movie*>::iterator it=
                graph.getMovieList()->begin(); it!=graph.getMovieList()->end(); it++)
            {
                if((*it).second->getYear()==yr&&(*it).second->getCast()->size()>1){
                    
                    yearPresent=true;
                    //break;
                }
            }
            if(!yearPresent) {
                continue;  //if there were no movie appear in a certain year, skip the iteration
            }
            
            graph.buildGraph(yr); //build the edges until year yr
            
            //check for paths for all pairs of actors
            
            
            
            for(int i=0; i<pairContainer->size();i++){
                
                //run BFS on each pair of actors
                Actor* start=pairContainer->at(i).first;
                Actor* end=pairContainer->at(i).second;
                
                graph.BFS(start, end);
                Actor* curr=end;
                bool connected=false;
                while(curr->prev.second){
                    if(curr->prev.second->getName()==start->getName()){
                        connected=true; //set the connected flag
                        break;
                    }
                    curr=curr->prev.second; //advance the curr pointer
                }
                if(!connected){
                    continue; //if the flag is not set, skip to the next iteration
                }
                //need to check if the same pair has been inserted in earlier year
                
                string str(start->getName()+'\t'+end->getName()+'\t');
                if(std::find(namePair->begin(), namePair->end(), str)==namePair->end()){
                    namePair->push_back(str); //store the name strings to eliminate
                    //duplicate pairs
                    std::pair<string,int> pairStr(str,yr);
                    connectedPair->insert(pairStr); //store the connected pair
                }
                
            }
            
        }
        
        
        outfile<<"Actor1\tActor2\tYear"<<endl;
        
        for(int i=0;i<pairContainer->size();i++){
            //find the name pair in order to output the pair in correct order
            string nameStr(pairContainer->at(i).first->getName()+'\t'
                           +pairContainer->at(i).second->getName()+'\t');
            unordered_map<string,int>::iterator it=connectedPair->find(nameStr);
            if(it!=connectedPair->end()) {
                outfile<<(*it).first<<(*it).second<<endl;
            }
            
            //if the pair are never connected at all after all possible years
            else {
                outfile<<nameStr<<"9999"<<endl;
            }
        }
        
        //free up previously allocated memory
        delete namePair;
        delete connectedPair;
        
        //end the timer and print out time taken
        cout<<"It takes "<<(timer.end_timer()/BILLION)<<" seconds to finish BFS!"<<endl;
    }
    ///////////////////////////////////using the BFS ends////////////////////////
    
    
    ///////////////////////////////////using union-find starts///////////////////
    
    else{  //if the fourth argument is not given, use ufind as default
        
        timer.begin_timer(); //start the timer
        
        //initialize the disjoint set
        UnionFind disjointSet=UnionFind(&graph);
        
        
        //use a vector to keep track of pairs, eliminate duplicate pairs in
        //different year
        vector<pair<string,string>>* namePair=new vector<pair<string,string>>();
        
        //use to store the connected pair to later ensure the correct printing order
        unordered_map<string,int>* connectedPair=new unordered_map<string,int>();
        //check for every year in the range
        for(int yr=earliestYear; yr<=latestYear; yr++) {
            bool yearPresent=false;
            
            
            //only build the disjoint set when there were movies in the certain year
            for(unordered_map<string,Movie*>::iterator it=
                graph.getMovieList()->begin(); it!=graph.getMovieList()->end(); it++)
            {
                if((*it).second->getYear()==yr&&(*it).second->getCast()->size()>1){
                    
                    yearPresent=true;
                    break;
                }
                
                if(!yearPresent) {
                    continue;  //if there were no movie appear in a certain year, skip the iteration
                }
                
            }
            
            for(unordered_map<string,Movie*>::iterator it=
                graph.getMovieList()->begin();it!=graph.getMovieList()->end();it++)
            {
                if((*it).second->getYear()==yr){
                    //if the cast of each movie in this year is greater than 1,
                    // union the actor nodes
                    Movie* currMovie=(*it).second;
                    for(int i=0; i<currMovie->getCast()->size()-1;i++){
                        
                        
                        Actor* actor1=currMovie->getCast()->at(i);
                        Actor* actor2=currMovie->getCast()->at(i+1);
                        
                        
                        disjointNode n1=disjointNode(actor1);
                        disjointNode n2=disjointNode(actor2);
                        
                        unordered_map<string,disjointNode*>::iterator it1=
                        disjointSet.upTreeMap->find(n1.getActor()->getName());
                        
                        unordered_map<string,disjointNode*>::iterator it2=
                        disjointSet.upTreeMap->find(n2.getActor()->getName());
                        
                        if((*it1).first!=(*it2).first){
                            //connect two set
                            
                            disjointSet.unionUnite((*it1).second, (*it2).second);
                            
                            
                        }
                        
                        //finished union operation
                    }
                    
                    
                    for(int i=0; i<pairContainer->size();i++) {
                        
                        string start=pairContainer->at(i).first->getName();
                        
                        string end=pairContainer->at(i).second->getName();
                        
                        
                        //find the start actor and end actor from the set
                        unordered_map<string,disjointNode*>::iterator itStart=
                        disjointSet.upTreeMap->find(start);
                        unordered_map<string,disjointNode*>::iterator itEnd=
                        disjointSet.upTreeMap->find(end);
                        
                        
                        //if start and end actors belong to the same set
                        if((*itStart).second->getSentinel()==(*itEnd).second->getSentinel()) {
                            pair<string,string> strPair(start,end);
                            //check if the pair is not yet printed
                            if(std::find(namePair->begin(), namePair->end(), strPair)
                               ==namePair->end()){
                                
                                namePair->push_back(strPair);
                                pair<string,int> connectedP(start+'\t'+end+'\t',yr);
                                connectedPair->insert(connectedP);
                            }
                            
                            
                        }
                        
                    }
                    
                }
            }
        }
        //ready to print
        outfile<<"Actor1\tActor2\tYear"<<endl;
        
        for(int i=0;i<pairContainer->size();i++){
            //find the name pair in order to output the pair in correct order
            string nameStr(pairContainer->at(i).first->getName()+'\t'
                           +pairContainer->at(i).second->getName()+'\t');
            unordered_map<string,int>::iterator it=connectedPair->find(nameStr);
            if(it!=connectedPair->end()) {
                outfile<<(*it).first<<(*it).second<<endl;
            }
            
            //if the pair are never connected at all after all possible years
            else {
                outfile<<nameStr<<"9999"<<endl;
            }
        }
        
        //free up previously allocated memory
        delete namePair;
        delete connectedPair;
        
        //end the timer and print out time taken
               cout<<"It takes "<<(timer.end_timer()/BILLION)<<" seconds to finish ufind!"<<endl;
    } ///////////////////////////////////using union-find ends///////////////////
    
    
    infile.close();
    outfile.close();
    
    
    //free up previously allocated memory
    delete pairContainer;
    
    cout<<"Actor connections finished!!"<<endl;
    return 0; //exit normally
}
