//
//  PancakeGraph.cpp
//  hw2
//
//  Created by Hang Chen on 9/21/18.
//  Copyright © 2018 Hang Chen. All rights reserved.
//

#include "PancakeGraph.hpp"
#include "PancakeNode.hpp"
#include <iostream>
#include <unordered_set>
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

void PancakeGraph::expandNode(PancakeNode *expandingNode, char algo) {
    
    PancakeNode *twoFlip = new PancakeNode(expandingNode->id, expandingNode->gCost);
    PancakeNode *threeFlip = new PancakeNode(expandingNode->id, expandingNode->gCost);
    PancakeNode *fourFlip = new PancakeNode(expandingNode->id, expandingNode->gCost);
    
    twoFlip->flip(2);
    threeFlip->flip(3);
    fourFlip->flip(4);
    
    twoFlip->parent = expandingNode;
    threeFlip->parent = expandingNode;
    fourFlip->parent = expandingNode;
    
    expandingNode->leftChild = twoFlip;
    expandingNode->middleChild = threeFlip;
    expandingNode->rightChild = fourFlip;
    
    PancakeNode *children [3];
    children[0] = twoFlip;
    children[1] = threeFlip;
    children[2] = fourFlip;
    
    for (int i = 0; i < 3; i++) {
        if (closedSet.find(children[i]->id) == closedSet.end()) {
            if (algo == 'u'){
                pqucs.push(children[i]);
            } else if (algo == 'g') {
                pqgreedy.push(children[i]);
            } else if (algo == 'a') {
                pqaStar.push(children[i]);
            }
        }

    }
    
//    if (closedSet.find(twoFlip->id) == closedSet.end()) {
//        if (algo == 'u'){
//            pqucs.push(twoFlip);
//        } else if (algo == 'g') {
//            pqgreedy.push(twoFlip);
//        } else if (algo == 'a') {
//            pqaStar.push(twoFlip);
//        }
//    }
    
//    if (closedSet.find(threeFlip->id) == closedSet.end())
//        pqucs.push(threeFlip);
//    if (closedSet.find(fourFlip->id) == closedSet.end())
//        pqucs.push(fourFlip);
    
}

void PancakeGraph::printPath(PancakeNode *goalNode) {
    PancakeNode *tmp = goalNode;
    while (tmp->parent != NULL) {
        this->printingStack.push(tmp);
        tmp = tmp->parent;
    }
    printingStack.push(tmp);
    
    while (printingStack.size() != 1) {
        PancakeNode firstNode = *printingStack.top();
        printingStack.pop();
        PancakeNode secondNode = *printingStack.top();
        cout << secondNode.flipFrom << " g=" << firstNode.gCost << ", h=" << firstNode.hCost << endl;
    }
    PancakeNode lastNode = *printingStack.top();
    cout << lastNode.id << " g=" << lastNode.gCost << ", h=" << lastNode.hCost << endl;
}

bool PancakeGraph::dfs() {
    return false;
}

bool PancakeGraph::ucs() {
    // Initial state
    // Push the root node to the fringe
    pqucs.push(root);
    while (pqucs.size() !=0) {
        PancakeNode &nodeToCheck = *pqucs.top();
        bool isGoal = checkGoalNode(&nodeToCheck);
        if (isGoal == true) {
            printPath(&nodeToCheck);
            return true;
        } else {
            pqucs.pop();
            closedSet.insert(nodeToCheck.id);
            expandNode(&nodeToCheck, 'u');
        }
    }
    return false;
}

bool PancakeGraph::greedy() {
    // Initial state
    // Push the root node to the fringe
    pqgreedy.push(root);
    while (pqgreedy.size() !=0) {
        PancakeNode &nodeToCheck = *pqgreedy.top();
        bool isGoal = checkGoalNode(&nodeToCheck);
        if (isGoal == true) {
            printPath(&nodeToCheck);
            return true;
        } else {
            pqgreedy.pop();
            closedSet.insert(nodeToCheck.id);
            expandNode(&nodeToCheck, 'g');
        }
    }
    return false;
}

bool PancakeGraph::aStar() {
    // Initial state
    // Push the root node to the fringe
    pqaStar.push(root);
    while (pqaStar.size() !=0) {
        PancakeNode &nodeToCheck = *pqaStar.top();
        bool isGoal = checkGoalNode(&nodeToCheck);
        if (isGoal == true) {
            printPath(&nodeToCheck);
            return true;
        } else {
            pqaStar.pop();
            closedSet.insert(nodeToCheck.id);
            expandNode(&nodeToCheck, 'a');
        }
    }
    return false;
}
