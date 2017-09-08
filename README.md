# Graph-Search-Six-Degrees-of-Kevin-Bacon-
Data structure project from 2017 winter at UC San Diego. Course: CSE 100 Advanced Data Structure

# Project Overview 

This is my final, and without doubt the most challenging, personal assignment in the course **Advanced Data Structure** 
( CSE 100 ) from **UC San Diego**

What I learned:

1. Write a program to play (and win) the generalized Kevin Bacon trivia game. My program will take as input ANY two 
actors/actresses and find the shortest sequence of shared movies between them.

2. Complete the weighted shortest path version of Pathfinder. I will also write a program that starts with one actor 
in the graph and adds new movies step-by-step to find the earliest movie year to connect the start actor to the destination 
actor.

**NOTE**: We were allowed to either team up with other students or try to complete the project alone. I chose to go **solo**.

#Language 

 This program is written in **C++**

# About "Six Degrees of Kevin Bacon" 

"Six Degrees of Kevin Bacon" is a parlor game based on the "six degrees of separation" concept, which posits that any two 
people on Earth are six or fewer acquaintance-links apart. That idea eventually morphed into this parlor game where movie 
buffs challenge each other to find the shortest path between an arbitrary actor and prolific Hollywood actor Kevin Bacon. 
It rests on the assumption that anyone involved in the Hollywood film industry can be linked through their film roles to 
Bacon within six steps. The game requires a group of players to try to connect any such individual to Kevin Bacon as quickly 
as possible and in as few links as possible.  In the first part of the assignment, I implemented the generalized version 
of the Kevin Bacon game. 


# Instructions below are copied from the original [assignment page](https://sites.google.com/a/eng.ucsd.edu/cse-100-winter-2017/assignments/assignment-4-readme)


0. Design and implement classes to support a graph implementation for the actor-movie relationships needed in this assignment.

In order to complete the rest of the assignment, you must first design your graph structure and implement the necessary classes. In your graph, each actor/actress will define a single node. Two nodes (i.e., actors) will be connected by an undirected edge if the corresponding actors played in the same movie.  Multiple undirected edges can exist between the same two nodes (which would imply that the two actors played in multiple movies together).   

Implementation Checklist: 

Review ActorGraph.cpp. This contains starter code to read the movie_casts.tsv file (the code open a file and parses the actor/movie/year from each line). For the implementations below, you may  have to create separate .cpp files for your different classes based on your design. 
Design/Implement your node objects (actors). What information does your node need to contain? 
Design/Implement your "edges." How will you connect actors (nodes), relationships (edges), and movies to each other that allows efficient traversal of the graph without needlessly copying whole objects around? Do you want to have a data structure for edges or merely represent them as connections between two nodes?  Pointers and/or vector indices might come in handy...
Check to make sure you did NOT use any pre-built data structures, like the Boost Graph Library (BGL), besides what is provided in the C++ STL data structures.
Test your graph implementation: load the movie_casts.tsv file, you should expect to find 11,794 actors or nodes, 14,252 movies, and 4,016,412 directed edges. Note: if we implement our graph with directed edges, every undirected edge will be represented by two directed edges. 
In a file called Report.pdf, place the answers to the following under a header called "Graph Design Analysis":
Describe the implementation of your graph structure (what new classes you wrote, what data structures you used, etc)
Describe *why* you chose to implement your graph structure this way (Is your design clean and easy to understand? what are you optimizing?, etc)
NOTE: If at any point your design changes, you MUST update Report.pdf to reflect this. If your report.pdf does not reflect your final implantation, you may lose points.  
Report.pdf will not be graded in the checkpoint and will be graded only in the final submission. 

1. Write a program called pathfinder (in pathfinder.cpp) to find the shortest path from one actor to another actor through shared movies. 

Implementation Checklist: 
Implement pathfinder to work on an unweighted graph (see ./pathfinder Details below for more information)
Read the grading notes below
Read the "Running Time" Notes at the bottom of the PA

./pathfinder Details

Your program should be called like this (see detailed explanation of arguments below):

> ./pathfinder movie_casts.tsv u test_pairs.tsv out_paths_unweighted.tsv

where test_pairs.tsv contains:

Actor1/Actress1 Actor2/Actress2
BACON, KEVIN (I)<TAB>HOUNSOU, DJIMON
BACON, KEVIN (I)<TAB>KIDMAN, NICOLE
BACON, KEVIN (I)<TAB>WILLIS, BRUCE
BACON, KEVIN (I)<TAB>GIAMATTI, PAUL
HOUNSOU, DJIMON<TAB>50 CENT

and your program produces an output file out_paths_unweighted.tsv containing the following (although the particular movies may not match, the total path weights should match your output):

(actor)--[movie#@year]-->(actor)--...
(BACON, KEVIN (I))--[ELEPHANT WHITE#@2011]-->(HOUNSOU, DJIMON)
(BACON, KEVIN (I))--[SUPER#@2010]-->(MCKAY, COLE S.)--[FAR AND AWAY#@1992]-->(KIDMAN, NICOLE)
(BACON, KEVIN (I))--[SUPER#@2010]-->(MORENO, DARCEL WHITE)--[LAY THE FAVORITE#@2012]-->(WILLIS, BRUCE)
(BACON, KEVIN (I))--[A FEW GOOD MEN#@1992]-->(MOORE, DEMI)--[DECONSTRUCTING HARRY#@1997]-->(GIAMATTI, PAUL)
(HOUNSOU, DJIMON)--[IN AMERICA#@2002]-->(MARTINEZ, ADRIAN (I))--[MORNING GLORY#@2010]-->(50 CENT)

./pathfinder will take 4 command-line arguments:

Name of text file containing the tab-delimited movie casts (such as movie_casts.tsv).

(movie_casts.tsv is very large, 6.4M. We have provided the smaller graphs that our submission scripts use for testing in  /home/linux/ieng6/cs100w/public/pa4/tsv/submissionScriptGraphs)
Lower-case character u or w

u -- builds the graph with unweighted edges

w -- builds the graph with weighted edges (you do not need to implement yet for checkpoint, but you will need to implement in final submission)
Name of text file containing the pairs of actors to find paths

First line in the file is a header, and each row contains the names of the two actors separated by a single tab character
Name of output text file

Pathfinder will create a new file to store the results from finding the shortest path between two actors

First line of the file is a header, and each row contains the paths for the corresponding pair of actors and input pairs file (in the same order).  Each path will be formatted as follows: (<actor name>)--[<movie title>#@<movie year>]-->(<actor name>)--[<movie title>#@<movie year>]-->(<actor name>)....etc where the movie listed between each pair of actors is one where they both had a role.


Grading Notes:
For the checkpoint, you are only required to have the unweighted portion of pathfinder working i.e. we will test your implementation with all 4 arguments except the second which we will always insert as a u
The specific path your pathfinder program outputs may be different than from reference solution. As long as the total path weights are the same, then you are fine.
Complete pathfinder is due at final submission, so if you don’t get the “unweighted edges” version working for the checkpoint, you must get it working by the final submission.
You may ONLY use C++ STL data structures and NOT the Boost Graph LIbrary (BGL). 
We have provided the test files that we use in our submission scripts in /home/linux/ieng6/cs100w/public/pa4/tsv/submissionScriptGraphs. Once you get it working on these small graphs, test them on larger graphs.   

 ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



Final Submission --- Deadline: Monday, March 13

1. Complete your pathfinder program by implementing the "weighted edges" version of your program, where edges will have a weight equal to the age of the movie (because we will want to choose newer movies over older movies when connecting two actors).

Implementation Checklist: 
Make pathfinder work for weighted graphs (see below for details) 
Read the "Running Time" Notes at the bottom of the PA

 If we are defining an edge between two actors that played in a movie made in year Y, then the weight of that edge will be:

weight = 1 + (2015 - Y)

Note that we are using 2015 instead of 2017, which is because the dataset only contains movies released in 2015 and earlier. Don't accidentally use 2017! 

Example:

> ./pathfinder movie_casts.tsv w test_pairs.tsv out_paths_weighted.tsv

should produce an output file out_paths_weighted.tsv containing the following (although the particular movies may not match, the total path weights should match your output):

(actor)--[movie#@year]-->(actor)--...
(BACON, KEVIN (I))--[ELEPHANT WHITE#@2011]-->(HOUNSOU, DJIMON)
(BACON, KEVIN (I))--[R.I.P.D.#@2013]-->(HUSS, TOBY (I))--[LITTLE BOY#@2015]-->(CHAPLIN, BEN)--[CINDERELLA#@2015]-->(MARTIN, BARRIE (II))--[PADDINGTON#@2014]-->(KIDMAN, NICOLE)
(BACON, KEVIN (I))--[R.I.P.D.#@2013]-->(BELTRAN, JONNY)--[THE WEDDING RINGER#@2015]-->(ROGERS, MIMI (I))--[CAPTIVE#@2015]-->(WILLIS, BRUCE)
(BACON, KEVIN (I))--[R.I.P.D.#@2013]-->(HOWARD, ROSEMARY (II))--[THE AMAZING SPIDER-MAN 2#@2014]-->(GIAMATTI, PAUL)
(HOUNSOU, DJIMON)--[THE VATICAN TAPES#@2015]-->(SCOTT, DOUGRAY)--[TAKEN 3#@2014]-->(HARVEY, DON (I))--[THE PRINCE#@2014]-->(50 CENT)

 The specific path your pathfinder program outputs may be different than from reference solution. As long as the total path weights are the same, then you are fine.

To efficiently implement Dijkstra's algorithm for shortest path in a weighted graph, you should make use of a priority queue. You can implement your own, or use the STL C++ implementation: http://www.cplusplus.com/reference/queue/priority_queue/. Note that it does not support an update_priority operation (how can you get around that?). Think about what happens if you insert the same key twice into the heap, but with a lower priority. Which one gets popped first? When you pop a key-priority pair, how do you know if it is valid/up-to-date or not?

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Actor Connections 

2. Implement a program called actorconnections. actorconnections should answer the following query: for every actor pair (X, Y) in the given list: "After which year did actors X and Y become connected?" By connected, we mean that there exists a path between actors X and Y in the equivalent movie graph (similar to that constructed in Part 1) with the exception that the movie graph under consideration only includes movies that were made until (i.e., before and including) a certain year. 

actorconnections will give the option to use two different approaches to solving the actor-connections problem: (1) using the graph structure itself, with BFS over particular edges in the graph (i.e. those up to a certain year) to determine whether two actors are connected and (2) without using the graph, but instead using the Disjont Set ADT that we will discuss in class.

Implementation Checklist:
Implement actor connections using the graph itself (and BFS): To answer queries about the connection between actor pairs using BFS, we recommend you start with an empty graph containing only actor names and incrementally add movies in increasing order of the year of the movie. Every time you add a new set of movies made in a specific year, actors that were not connected before may become connected, which can be determined by running BFS on the updated graph.
Implement actor connections without using the graph, instead using the Disjoint Set ADT: Alternatively, the disjoint-set (i.e., "union-find") data structure allows you to keep track of all connected sets of actors without maintaining the corresponding graph structure. You might still consider adding movies incrementally, and if a movie creates a path between two actors that were not connected before, two disjoint sets would be merged into a single set in your union-find data structure. You should be able to then query your data structure about the connectivity of any specific actor pairs. The performance of your implementation will naturally depend on the efficiency of your Union-Find data structure. We will go over these topics in lecture  and discussion as well. Your implementation MUST be very efficient. 
Review the edge cases checklist below
Test against refactorconnections (see Reference Solution below)
Read the "Running Time" Notes at the bottom of the PA
./actorconnections Details

> ./actorconnections movie_casts.tsv test_pairs.tsv out_connections_bfs.tsv ufind

should run your code (using the union-find algorithm) to produce an output file out_connections_bfs.tsv containing the following:

Actor1<TAB>Actor2<TAB>Year
BACON, KEVIN (I)<TAB>HOUNSOU, DJIMON<TAB>1992
BACON, KEVIN (I)<TAB>KIDMAN, NICOLE<TAB>1991
BACON, KEVIN (I)<TAB>WILLIS, BRUCE<TAB>1990
BACON, KEVIN (I)<TAB>GIAMATTI, PAUL<TAB>1992
HOUNSOU, DJIMON<TAB>50 CENT<TAB>2003



actorconnections will take 4 command-line arguments:
The first argument is the name of a text file containing the movie casts in the same format as movie_casts.tsv. Again, this file is quite large (6.4M), so you should create smaller versions to test your implementation as a first step. We have provided the smaller graphs that our submission scripts use for testing in  /home/linux/ieng6/cs100w/public/pa4/tsv/submissionScriptGraphs. Once you get it working on these graphs, test it on larger graphs and movie_casts.tsv. 
The second argument is the name of a text file containing the names of actor pairs on each line separated, with the two actor names are tab-separated (same format as test_pairs.tsv).
The third argument is the name of your output text file, which should contain in each line an actor pair followed by the year (tab-separated) after which the corresponding actor pair became connected (you will do all actor pairs specified in the file from step 2, one on each line). If two actors are never connected or if one or both of the actors is not in the movie cast file given to you, simply append 9999 in the corresponding line of the output file. To further clarify, if the second argument was a file containing the actor pair "BLANCHETT, CATE" and "REEVES, KEANU" and they only became connected after adding a movie made in 1997, your program should output the actor pair and 1997 in their line of the output file. If they never became connected even after adding all the movies from in the movie cast file to your graph, you should output 9999 on that line.
The fourth argument should be specified as either bfs or ufind. This option determines which algorithm will be used in your program. If the fourth argument is not given, by default your algorithm should use the union-find data structure (i.e., the equivalent of specifying ufind as the fourth argument). We will test your code with both flags.
Edge Cases Checklist: 
 We will not test you on the corner case where both the actors are the same. You can handle it however you want. 

Reference Solution: 
We have made a reference solution available on ieng6 in the following location:
/home/linux/ieng6/cs100w/public/pa4/refactorconnections
/home/linux/ieng6/cs100w/public/pa4/refpathfinder

The usage for running union find is:
./refactorconnections movie_cast_file.tsv pair_file.tsv output_file.tsv ufind

OR:
./refactorconnections movie_cast_file.tsv pair_file.tsv output_file.tsv


The usage for running the BFS implementation is:
./refactorconnections movie_cast_file.tsv pair_file.tsv output_file.tsv bfs

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Actorconnections running time comparison (Report.pdf) 

 3. Compare the run times of each implementation on a file containing actor pair pairs that you generate yourself. See how the run times compare when you repeat the same query multiple times. The file should be in the same format as test_pairs.tsv. 

Implementation Checklist:
Calculate runtimes of each implementation. The first argument should be movie_casts.tsv. 
In your input file (specified as the second argument), have the same actor pair appear 100 times and calculate the time it took to answer all 100 queries using your BFS implementation and then using your union-find implementation. For your code, you can use the timing classes given to you in PA2. 
In your input file (specified as the second argument), have 100 different actor pairs  and calculate the time it took to answer all 100 queries using your BFS implementation and then using your union-find implementation. For your code, you can use the timing classes given to you in PA2.  pair.tsv has 100 different actor pairs. 
In  the same Report.pdf where you explained the class design (see part 0 of the checkpoint for more details) , place the answers to the following questions under a header called "Actor connections running time":
Which implementation is better and by how much? 
When does the union-find data structure significantly outperform BFS (if at all)?
What arguments can you provide to support your observations?
Do not forget that the Report.pdf will contain answers to questions on the class design (see part0 of the checkpoint) and the above questions. 


# Author 

[@Daniel](https://www.linkedin.com/in/daniel-huang-443546115/)
