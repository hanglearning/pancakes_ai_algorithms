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

using namespace std;

class PancakeGraph {
    
    // closed set to store expanded nodes to avoid expanding them again
    // https://www.geeksforgeeks.org/unorderd_set-stl-uses/
    unordered_set<int> closedSet;
    
    priority_queue<PancakeNode, vector<PancakeNode>, cmpGCost> pqdfs;
    priority_queue<PancakeNode, vector<PancakeNode>, cmpGCost> pqucs;
    priority_queue<PancakeNode, vector<PancakeNode>, cmpHCost> pqgreedy;
    priority_queue<PancakeNode, vector<PancakeNode>, cmpGandHCost> pqastar;
    
    
    
public:
    PancakeGraph(PancakeNode *rootNode);
    PancakeNode *root;
    // used to expend the input node by the three flipping options
    bool checkGoalNode(PancakeNode *currNode);
    void expandNode(PancakeNode *expendingNode);
    void printPath(PancakeNode *goalNode);
    
    bool dfs();
    bool ucs();
    bool greedy();
    bool aStar();
    
    
};

// https://www.youtube.com/watch?v=iJ-NSxH3QNc
// https://www.geeksforgeeks.org/binary-heap/
// https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator

// comparator function used with the priority queue to get the node having the least culmulative cost from the fringe
class cmpGCost {
public:
    bool operator()(PancakeNode *a, PancakeNode *b) {
        return a->getGCost() > b->getGCost();
    }
};

// comparator function to get the node having the least heuristic cost from the fringe
class cmpHCost {
public:
    bool operator()(PancakeNode *a, PancakeNode *b) {
        return a->getHCost() > b->getHCost();
    }
};

// comparator function to get the node having the least sum of the culmulative cost and the heuristic cost from the fringe
class cmpGandHCost {
public:
    bool operator()(PancakeNode *a, PancakeNode *b) {
        return ((a->getHCost() + a->getGCost()) > (b->getHCost() + b->getGCost()));
    }
};


// comparator function used with the priority queue to get the node having the largest id number from the fringe
class cmpID {
public:
    bool operator()(PancakeNode *a, PancakeNode *b) {
        return a->getId() < b->getId();
    }
};

#endif /* PancakeGraph_hpp */
