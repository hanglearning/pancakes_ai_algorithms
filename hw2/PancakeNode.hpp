//
//  PancakeNode.hpp
//  hw2
//
//  Created by Hang Chen on 9/20/18.
//  Copyright © 2018 Hang Chen. All rights reserved.
//

#ifndef PancakeNode_hpp
#define PancakeNode_hpp

#include <stdio.h>
#include <string>

using namespace std;
const int MAXCHILDREN = 3;

class PancakeNode {
    
    int id;     // the pancake order state in this node, such as 2314
    int gCost;      // the culmulative cost from the start node to the current node
    int hCost;      // the heuristic value of the current node to the goal
    string flipFrom; // used to record the previous flipping state to this state, e.g. 4321 is from 43|12
    PancakeNode *parent;    // parent node of the current pancakeNode
    PancakeNode *children[MAXCHILDREN];     // 3 flipping options make 3 chidren nodes for the current pancakeNode
    
public:
    PancakeNode(int id);    // constructor with initializing the id
    void flip(int flips);    // function used to flip the pancakes
    int getLargestPancakeId();  //function used to get the largest pancake id that's still out of place to set the heuristic cost of a certain pancake node
    
    // getters and setters
    int getId();
    void setGCost(int gCostArc);   // the gCostArc parimeter is the arc cost from its parent node to itself
    int getGCost();
    void setHCost();
    int getHCost();
    
};

#endif /* PancakeNode_hpp */
