

/*
 * pathfinder.cpp
 * Author: Daniel Huang
 * Date:   3/03/2017
 *
 * This file is implemented to find the shortest path between two actors in the graph
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "ActorGraph.h"
#include "Movie.h"
#include "Actor.h"

using namespace std;
int main(int argc, char* argv[]) {
    //check the number of arguments first
    if(argc!=5) {
        cout<<"Invalid number of arguments, please try again"<<endl;
        return -1;
    }
    
    ActorGraph graph= ActorGraph();
    
    
    //for the checkpoint, 'u' will always be passed in
    if(*(argv[2])=='u') {
        graph.loadFromFile(argv[1], false);
        graph.weighted=false;
    }
    else if (*(argv[2])=='w') {
        graph.loadFromFile(argv[1], true);
        graph.weighted=true;
    }
    
    
    //build the actual graph representation of actors and movies
    graph.buildGraph();
    
    
    
    ifstream infile(argv[3]);  //open the test_pairs file
    
    ofstream outfile(argv[4]); //initialize the output file stream
    
    outfile<<"(actor)--[movie#@year]-->(actor)--..."<<endl; //write the header for
    //the output
    bool have_header = false;
    
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
        vector <string> record;
        
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
        Actor actor1=Actor(name1);
        
        //cout<<name1<<" is the actor of this row"<<endl;
        
        unordered_map<string, Actor*>::iterator start=graph.getActorList()->find(record[0]);
        
        //check for possible edge case where the actor pair is not found
        if(start==graph.getActorList()->end()) {
            cout<<"The actor pair is not found, please change your pair tsv file"<<endl;
            return -1;
        }
        
        name2=string(record[1]);
        Actor actor2=Actor(name2);
        
        
        
        unordered_map<string, Actor*>::iterator end=graph.getActorList()->find(record[1]);
        
        
        if(!graph.weighted) { //unweighted graph, use BFS
            for(unordered_map<string,Actor*>::iterator it=graph.getActorList()->begin(); it!=graph.getActorList()->end(); it++){
                (*it).second->setDist(numeric_limits<int>::max());  //set all nodes' distance to infinity
                std::pair<Movie*,Actor*> nullpair(0,0);
                (*it).second->prev=nullpair;   //reset the prev for all nodes
            }

            graph.BFS((*start).second, (*end).second); //start from actor1
        }
        else { //weighted graph, use Dijkstra's algorithm
            graph.Dij((*start).second);
        }
        
        stack<string> st = stack <string>(); //initialize a stack for printing out path
        Actor* curr=(*end).second;            //actor2 as the end node
        
        st.push("("+curr->getName()+")"); //store the actor name
        
        while(curr->prev.first) {
            
            
            st.push("--["+curr->prev.first->getName()+"]-->");
            st.push("("+curr->prev.second->getName()+")");
            
            if(curr->prev.second->getName()==name1){
                break;
            }
            curr=curr->prev.second; //advance the curr pointer
            
        }
        //st.push("("+name1+")");  //lastly push the first starting actor(since it
        //would not have prev
        while(!st.empty()){
            outfile<<st.top(); //write to the output file
            st.pop();
        }
        
        outfile<<"\n";
        
        
        
        
    }
    
    //for debugging
    // cout<<"the size of actor list is "<<graph.getActorList()->size()<<endl;
    for(unordered_map<string,Actor*>::iterator it=graph.getActorList()->begin();
        it!=graph.getActorList()->end(); it++)
    {
        
        // cout<<"print every actor in the list: "<<(*it).second->getName()<<endl;
        //cout<<"And the distance of the above actor is "<<(*it).second->getDist()<<endl;
        // cout<<"the edges size of "<<(*it).second->getName()<<" is: "<<(*it).second->edges->size()<<endl;
        for(int i=0; i<(*it).second->edges->size();i++){
            //    cout<<(*it).second->getName()<<" is connected to ";
            //  cout<<(*it).second->edges->at(i).second->getName()<<endl;
        }
        if((*it).second->prev.second) {
            //   cout<<"the prev of actor: "<<(*it).second->getName()<<" is "<<(*it).second->prev.second->getName()<<endl;
        }
    }
    
    
    
    //at this point we have read all test pairs
    infile.close();
    outfile.close();
    
    return 0;
    
}
