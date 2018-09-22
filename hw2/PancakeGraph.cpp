//
//  PancakeGraph.cpp
//  hw2
//
//  Created by Hang Chen on 9/21/18.
//  Copyright © 2018 Hang Chen. All rights reserved.
//

#include "PancakeGraph.hpp"
#include "PancakeNode.hpp"
using namespace std;

const int GOALSTATE = 4321;

PancakeGraph::PancakeGraph(PancakeNode *rootNode){
    root = rootNode;
}

bool PancakeGraph::checkGoalNode(PancakeNode *currNode) {
    if (currNode->id == GOALSTATE) {
        return true;
    } else {
        return false;
    }
}

void PancakeGraph::expandNode(PancakeNode *expandingNode) {
    
    PancakeNode *twoFlip = expandingNode;
    PancakeNode *threeFlip = expandingNode;
    PancakeNode *fourFlip = expandingNode;
    
    twoFlip->flip(2);
    threeFlip->flip(3);
    fourFlip->flip(4);
    
    twoFlip->parent = expandingNode;
    threeFlip->parent = expandingNode;
    fourFlip->parent = expandingNode;
    
    expandingNode->leftChild = twoFlip;
    expandingNode->middleChild = threeFlip;
    expandingNode->rightChild = fourFlip;
    
    if (closedSet.find(twoFlip) == stringSet.end())
        pqucs.push(twoFlip);
    if (closedSet.find(threeFlip) == stringSet.end())
        pqucs.push(threeFlip);
    if (closedSet.find(fourFlip) == stringSet.end())
        pqucs.push(fourFlip);
    
}

void PancakeGraph::printPath(PancakeNode *goalNode) {
    while (goalNode->parent != NULL) {
        cout << "print test" << endl;
    }
}

bool PancakeGraph::ucs() {
    // Initial state
    // Push the root node to the fringe
    pqucs.push(root);
    while (pqucs.size !=0) {
        PancakeNode *nodeToCheck = pducs.top();
        bool isGoal = checkGoalNode(nodeToCheck);
        if (isGoal == true) {
            printPath(nodeToCheck);
        } else {
            pducs.pop();
            closedSet.insert(nodeToCheck);
            expandNode(nodeToCheck);
        }
    }
    return false;
}
