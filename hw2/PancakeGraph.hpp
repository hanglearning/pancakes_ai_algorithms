//
//  PancakeGraph.hpp
//  hw2
//
//  Created by Hang Chen on 9/21/18.
//  Copyright © 2018 Hang Chen. All rights reserved.
//

#ifndef PancakeGraph_hpp
#define PancakeGraph_hpp

#include "PancakeNode.hpp"
#include <stdio.h>
#include <unordered_set>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

// following four functions define four comparators for the priority queues used with the algorithm

// comparator function used with the priority queue to get the node having the least culmulative cost from the fringe.
// used in UCS
class cmpGCost {
public:
    bool operator()(PancakeNode *a, PancakeNode *b) {
        return a->getGCost() > b->getGCost();
    }
};

// comparator function to get the node having the least heuristic cost from the fringe
// used in Greedy
class cmpHCost {
public:
    bool operator()(PancakeNode *a, PancakeNode *b) {
        return a->getHCost() > b->getHCost();
    }
};

// comparator function to get the node having the least sum of the culmulative cost and the heuristic cost from the fringe
// used in A*
class cmpGandHCost {
public:
    bool operator()(PancakeNode *a, PancakeNode *b) {
        return ((a->getHCost() + a->getGCost()) > (b->getHCost() + b->getGCost()));
    }
};


// comparator function used with the priority queue to get the node having the largest id number from the fringe
// used in DFS, and a helper queue for all other 3 algorithms
class cmpID {
public:
    bool operator()(PancakeNode *a, PancakeNode *b) {
        return a->getId() < b->getId();
    }
};

class PancakeGraph {
    
    // closed set to store expanded nodes to avoid expanding them again
    unordered_set<int> closedSet;
    
    // used for printing the output
    // see printPath() for details
    stack <PancakeNode*> printingStack;
    
    // prioritt queues used in four algorithms respectively
    priority_queue<PancakeNode*, vector<PancakeNode*>, cmpID> pqdfs;
    priority_queue<PancakeNode*, vector<PancakeNode*>, cmpGCost> pqucs;
    priority_queue<PancakeNode*, vector<PancakeNode*>, cmpHCost> pqgreedy;
    priority_queue<PancakeNode*, vector<PancakeNode*>, cmpGandHCost> pqaStar;
    
    // helper queue to always store the node with the highest id number to determine tie
    priority_queue<PancakeNode*, vector<PancakeNode*>, cmpID> pqid;
    
    
    
public:
    
    // constructor
    PancakeGraph(PancakeNode *rootNode);
    
    // root node of the graph
    PancakeNode *root;
    
    // check if the node is the goal node
    bool checkGoalNode(PancakeNode *currNode);
    
    // used to expend the input node by the three flipping options
    // the expendingNode is the parent node to be expanded, and
    // the char algo is used to determine which fringe the children
    // nodes are to put in. see the actual function for details
    void expandNode(PancakeNode *expendingNode, char algo);
    
    // used to print the output
    // see the actual function for details
    void printPath(PancakeNode *goalNode);
    
    // four searching algorithms
    // return true if path is found,
    // otherwise false
    bool dfs();
    bool ucs();
    bool greedy();
    bool aStar();
    
    
};

#endif /* PancakeGraph_hpp */
