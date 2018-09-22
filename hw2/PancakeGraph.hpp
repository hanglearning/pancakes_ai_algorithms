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
using namespace std;

class PancakeGraph {
    
    // closed set to store expanded nodes to avoid expanding them again
    // https://www.geeksforgeeks.org/unorderd_set-stl-uses/
    unordered_set<int> closedSet;
    
    
Public
    PancakeGraph();
    PancakeNode *root;
    void expandNode();
    void compare
}

#endif /* PancakeGraph_hpp */
