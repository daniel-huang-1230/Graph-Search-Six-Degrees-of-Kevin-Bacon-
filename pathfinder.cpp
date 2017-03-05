

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
    }
    else if (*(argv[2])=='w') {
        graph.loadFromFile(argv[1], true);
    }
    
    graph.buildGraph();

       //build the actual graph representation of actors and movies
    
    
    ifstream infile;  //open the test_pairs file
    infile.open(argv[3]);
    ofstream outfile(argv[4]); //initialize the output file stream
    
    outfile<<"(actor)--[movie#@year]-->(actor)--..."<<endl; //write the header for
                                                            //the output 
    bool have_header = false;
    
   
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
            
        string name1(record[0]);
        Actor actor1=Actor(name1);
      
        //Actor got1=graph.findActor(actor1.getName());
        unordered_map<string, Actor>::iterator got1=graph.getActorList()->find(record[0]);
        
        string name2(record[1]);
        Actor actor2=Actor(name2);
        
        unordered_map<string, Actor>::iterator got2=graph.getActorList()->find(record[1]);
        
        
        //Actor got2=graph.findActor(actor2.getName());
            
            graph.BFS(&(*got1).second); //start from actor1
          
        
    
            stack<Movie*> st = stack <Movie*>(); //initialize a stack for printing out path
            Actor* curr=&(*got2).second;            //actor2 as the end node
        
       
            /*while(curr->getEdge().second) { //traverse to the previous actor connected by an edge
               st.push(curr->getEdge().first);

                curr=curr->getEdge().second; //advance the curr pointer
            }
            outfile<<"--["<<st.top()->getName()<<"]"; //print the movie title
            st.pop();*/
            
         
        }
    
    //for debugging....
    for(unordered_map<string, Actor>::iterator it=graph.getActorList()->begin();it!=graph.getActorList()->end();it++){
        cout<<(*it).second.getDist()<<endl;
      //  vector<Actor* > adjList= (*it).second.getAdj();
        //cout<<adjList.size()<<endl;
    }
    //cout<<graph.getActorList()->size()<<endl;
    //cout<<graph.getMovieList()->size()<<endl;
   
    infile.close();
    outfile.close();
   
    return 0;
}
