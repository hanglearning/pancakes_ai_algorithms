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

// goal state can be changed here
const int GOALSTATE = 4321;

// Graph constructor with initializing the root node
PancakeGraph::PancakeGraph(PancakeNode *rootNode){
    root = rootNode;
}

// check if this node contains the goal state
bool PancakeGraph::checkGoalNode(PancakeNode *currNode) {
    if (currNode->id == GOALSTATE) {
        return true;
    } else {
        return false;
    }
}

// used to expand the certain node after being checked as a non-goal node
// the function will expand the nodes by 3 flipping options and add the yielded
// nodes as the children of this expandedNode, and then add those children nodes
// to the fringe. This expanded node will also be popped off the fringe outside
// this function
void PancakeGraph::expandNode(PancakeNode *expandingNode, char algo) {
    
    // make children nodes as the clone of their parent node
    PancakeNode *twoFlip = new PancakeNode(expandingNode->id, expandingNode->gCost);
    PancakeNode *threeFlip = new PancakeNode(expandingNode->id, expandingNode->gCost);
    PancakeNode *fourFlip = new PancakeNode(expandingNode->id, expandingNode->gCost);
    
    // flip these nodes to their established orders
    twoFlip->flip(2);
    threeFlip->flip(3);
    fourFlip->flip(4);
    
    // don't forget who gave you lives
    twoFlip->parent = expandingNode;
    threeFlip->parent = expandingNode;
    fourFlip->parent = expandingNode;
    
    // mom never forgets their children
    expandingNode->leftChild = twoFlip;
    expandingNode->middleChild = threeFlip;
    expandingNode->rightChild = fourFlip;
    
    // construct an array of children for the
    // convenience of looping through them and add
    // them to the fringe
    PancakeNode *children [3];
    children[0] = twoFlip;
    children[1] = threeFlip;
    children[2] = fourFlip;
    
    // add them to the corresponding frienge
    for (int i = 0; i < 3; i++) {
        if (closedSet.find(children[i]->id) == closedSet.end()) {
            if (algo == 'u'){
                pqucs.push(children[i]);
                pqid.push(children[i]);     // a helper priority queue is used to break the tie
            } else if (algo == 'g') {
                pqgreedy.push(children[i]);
                pqid.push(children[i]);
            } else if (algo == 'a') {
                pqaStar.push(children[i]);
                pqid.push(children[i]);
            } else if (algo == 'd') {
                pqdfs.push(children[i]);
            }
        }
        
    }
    
}

// used to loop from the goal node to the starting node
// and then print the path from the starting node to the
// end node, with the corresponding g cost and h cost based
// on the requirement
void PancakeGraph::printPath(PancakeNode *goalNode) {
    PancakeNode *tmp = goalNode;
    
    // since back reversal is not the required printing order,
    // I created a LIFO printing stack to "reverse" the path
    while (tmp->parent != NULL) {
        this->printingStack.push(tmp);
        tmp = tmp->parent;
    }
    printingStack.push(tmp);
    
    // print
    while (printingStack.size() != 1) {
        PancakeNode firstNode = *printingStack.top();
        printingStack.pop();
        PancakeNode secondNode = *printingStack.top();
        cout << secondNode.flipFrom << " g=" << firstNode.gCost << ", h=" << firstNode.hCost << endl;
    }
    PancakeNode lastNode = *printingStack.top();
    cout << lastNode.id << " g=" << lastNode.gCost << ", h=" << lastNode.hCost << endl;
}

/* depth first search algorithm - since it doesn't depend
 on g and h, every expanding node is a tie, and we simply
 go to the node that has the highest id */
bool PancakeGraph::dfs() {
    // pqdfs is a priority queue, which the comparator putting
    // the node with the largest id at the top
    pqdfs.push(root);
    
    // if fringe is not empty
    while (pqdfs.size() != 0) {
        // pop the one with the largest id to check
        PancakeNode &nodeToCheck = *pqdfs.top();
        // check if this node is the goal
        bool isGoal = checkGoalNode(&nodeToCheck);
        // if it is, print the path and exit the program
        if (isGoal == true) {
            printPath(&nodeToCheck);
            return true;
        } else {
            // if not, deque the node, add to the closed set,
            // and expand the node
            // (though this should be put above checkGoalNode()
            // since we always check the goal when we dequeue a goal)
            pqdfs.pop();
            closedSet.insert(nodeToCheck.id);
            expandNode(&nodeToCheck, 'd');
        }
    }
    return false;
}

/* uniform cost search algorithm -
 always go with the lowest
 g cost on the fringe */
bool PancakeGraph::ucs() {
    // Initial state
    // Push the root node to the fringe
    pqucs.push(root);
    // a helper priority queue having the largest id node at front to check for the tie
    pqid.push(root);
    
    // stack used to put the nodes back to the fringe when doing tie checking
    stack <PancakeNode*> tmpStack;
    
    bool tie = false;
    int tmpStackSize;
    
    // when there's node in the fringe, perform the algorithm, otherwise return failure
    while (pqucs.size() != 0) {
        
        // this is used to check if there's tie in the fringe
        if (pqucs.size() != 1){
            // check for tie
            PancakeNode *firstFriengeNode = pqucs.top();
            pqucs.pop();
            PancakeNode *secondFriengeNode = pqucs.top();
            if (firstFriengeNode->getGCost() == secondFriengeNode->getGCost()){
                tie = true;
            }
            pqucs.push(firstFriengeNode);
        }
        
        // if there's no tie, check the first item in the priority queue
        // with the least g cost at the top
        if(tie == false) {
            PancakeNode &nodeToCheck = *pqucs.top();
            bool isGoal = checkGoalNode(&nodeToCheck);
            if (isGoal == true) {
                printPath(&nodeToCheck);
                return true;
            } else {
                // unlike dfs, if it's not goal here, we have to make sure
                // the helper queue pqid works in parellel
                pqucs.pop();
                while (pqid.top()->getId() != nodeToCheck.getId()){
                    tmpStack.push(pqid.top());
                    pqid.pop();
                }
                pqid.pop();
                tmpStackSize = tmpStack.size();
                for (int i = 0; i < tmpStackSize; i++){
                    pqid.push(tmpStack.top());
                    tmpStack.pop();
                }
                closedSet.insert(nodeToCheck.id);
                expandNode(&nodeToCheck, 'u');
            }
            
        } else {
            /* if there's a tie, pqid comes to rescue */
            
            // if the first node in the fringe has the same g cost
            // with the first node in the helper queue(with the largest
            // id as the first node), then the first node in the helper
            // helper queue is the node we want to check.
            // But we need to pop that node from the fringe as well,
            // so we loop through the fringe to find the node that's
            // identical  to the first node in the helper queue,
            // check it and perform the algorithm
            if (pqucs.top()->getGCost() == pqid.top()->getGCost()) {
                while (pqucs.top()->getId() != pqid.top()->getId()) {
                    tmpStack.push(pqucs.top());
                    pqucs.pop();
                }
                PancakeNode &nodeToCheck = *pqucs.top();
                bool isGoal = checkGoalNode(&nodeToCheck);
                if (isGoal == true) {
                    printPath(&nodeToCheck);
                    return true;
                } else {
                    pqid.pop();
                    pqucs.pop();
                    closedSet.insert(nodeToCheck.id);
                    expandNode(&nodeToCheck, 'u');
                    tmpStackSize = tmpStack.size();
                    for (int i = 0; i < tmpStackSize; i++) {
                        pqucs.push(tmpStack.top());
                        tmpStack.pop();
                    }
                }
                
            // if the first node in the fringe doesn't have the same g cost
            // with the first node in the helper queue(with the largest
            // id as the first node), then we have to loop through the helper
            // queue to find the first node that has the same g cost as the
            // first node in the fringe, then we find that node in the fringe,
            // pop off to check, and also push back the irrelavant nodes popped
            // off from both queues
            } else {
                while (pqucs.top()->getGCost() != pqid.top()->getGCost()) {
                    tmpStack.push(pqid.top());
                    pqid.pop();
                }
                PancakeNode &nodeToCheck = *pqid.top();
                bool isGoal = checkGoalNode(&nodeToCheck);
                if (isGoal == true) {
                    printPath(&nodeToCheck);
                    return true;
                } else {
                    pqid.pop();
                    closedSet.insert(nodeToCheck.id);
                    expandNode(&nodeToCheck, 'u');
                    tmpStackSize = tmpStack.size();
                    for (int i = 0; i < tmpStackSize; i++) {
                        pqid.push(tmpStack.top());
                        tmpStack.pop();
                    }
                    while (pqucs.top()->getId() != nodeToCheck.getId()){
                        tmpStack.push(pqucs.top());
                        pqucs.pop();
                    }
                    pqucs.pop();
                    tmpStackSize = tmpStack.size();
                    for (int i = 0; i < tmpStackSize; i++) {
                        pqucs.push(tmpStack.top());
                        tmpStack.pop();
                    }
                }
            }
        }
        
        
    }
    return false;
}

/* greedy saerch, always go to the node with the lowest h cost on the fringe.
 This algorithm is quite similar to ucs, except it uses the priority queue that
 orders the nodes by ascending order of h. So no more detailed comments in the
 algorithm code block */
bool PancakeGraph::greedy() {
    // Initial state
    // Push the root node to the fringe
    pqgreedy.push(root);
    pqid.push(root);
    stack <PancakeNode*> tmpStack;
    bool tie = false;
    int tmpStackSize;
    
    while (pqgreedy.size() != 0) {
        if (pqgreedy.size() != 1){
            // check for tie
            PancakeNode *firstFriengeNode = pqgreedy.top();
            pqgreedy.pop();
            PancakeNode *secondFriengeNode = pqgreedy.top();
            if (firstFriengeNode->getHCost() == secondFriengeNode->getHCost()){
                tie = true;
            }
            pqgreedy.push(firstFriengeNode);
        }
        if(tie == false) {
            PancakeNode &nodeToCheck = *pqgreedy.top();
            bool isGoal = checkGoalNode(&nodeToCheck);
            if (isGoal == true) {
                printPath(&nodeToCheck);
                return true;
            } else {
                pqgreedy.pop();
                while (pqid.top()->getId() != nodeToCheck.getId()){
                    tmpStack.push(pqid.top());
                    pqid.pop();
                }
                pqid.pop();
                tmpStackSize = tmpStack.size();
                for (int i = 0; i < tmpStackSize; i++){
                    pqid.push(tmpStack.top());
                    tmpStack.pop();
                }
                closedSet.insert(nodeToCheck.id);
                expandNode(&nodeToCheck, 'g');
            }
            
        } else {
            if (pqgreedy.top()->getHCost() == pqid.top()->getHCost()) {
                while (pqgreedy.top()->getId() != pqid.top()->getId()) {
                    tmpStack.push(pqgreedy.top());
                    pqgreedy.pop();
                }
                PancakeNode &nodeToCheck = *pqgreedy.top();
                bool isGoal = checkGoalNode(&nodeToCheck);
                if (isGoal == true) {
                    printPath(&nodeToCheck);
                    return true;
                } else {
                    pqid.pop();
                    pqgreedy.pop();
                    closedSet.insert(nodeToCheck.id);
                    expandNode(&nodeToCheck, 'g');
                    tmpStackSize = tmpStack.size();
                    for (int i = 0; i < tmpStackSize; i++) {
                        pqgreedy.push(tmpStack.top());
                        tmpStack.pop();
                    }
                }
            } else {
                while (pqgreedy.top()->getHCost() != pqid.top()->getHCost()) {
                    tmpStack.push(pqid.top());
                    pqid.pop();
                }
                PancakeNode &nodeToCheck = *pqid.top();
                bool isGoal = checkGoalNode(&nodeToCheck);
                if (isGoal == true) {
                    printPath(&nodeToCheck);
                    return true;
                } else {
                    pqid.pop();
                    closedSet.insert(nodeToCheck.id);
                    expandNode(&nodeToCheck, 'g');
                    tmpStackSize = tmpStack.size();
                    for (int i = 0; i < tmpStackSize; i++) {
                        pqid.push(tmpStack.top());
                        tmpStack.pop();
                    }
                    while (pqgreedy.top()->getId() != nodeToCheck.getId()){
                        tmpStack.push(pqgreedy.top());
                        pqgreedy.pop();
                    }
                    pqgreedy.pop();
                    tmpStackSize = tmpStack.size();
                    for (int i = 0; i < tmpStackSize; i++) {
                        pqgreedy.push(tmpStack.top());
                        tmpStack.pop();
                    }
                }
            }
        }
        
        
    }
    return false;
}

/* a star saerch, always go to the node with the lowest sum of the g cost and
 the h cost on the fringe.
 This algorithm is quite similar to ucs and greedy, except it uses the
 priority queue that orders the nodes by ascending order of g+h.
 So no more detailed comments in the algorithm code block */
bool PancakeGraph::aStar() {
    // Initial state
    // Push the root node to the fringe
    pqaStar.push(root);
    pqid.push(root);
    stack <PancakeNode*> tmpStack;
    bool tie = false;
    int tmpStackSize;
    
    while (pqaStar.size() != 0) {
        
        if (pqaStar.size() != 1){
            // check for tie
            PancakeNode *firstFriengeNode = pqaStar.top();
            pqaStar.pop();
            PancakeNode *secondFriengeNode = pqaStar.top();
            if (firstFriengeNode->getFCost() == secondFriengeNode->getFCost()){
                tie = true;
            }
            pqaStar.push(firstFriengeNode);
        }
        
        if(tie == false) {
            PancakeNode &nodeToCheck = *pqaStar.top();
            bool isGoal = checkGoalNode(&nodeToCheck);
            if (isGoal == true) {
                printPath(&nodeToCheck);
                return true;
            } else {
                pqaStar.pop();
                while (pqid.top()->getId() != nodeToCheck.getId()){
                    tmpStack.push(pqid.top());
                    pqid.pop();
                }
                pqid.pop();
                tmpStackSize = tmpStack.size();
                for (int i = 0; i < tmpStackSize; i++){
                    pqid.push(tmpStack.top());
                    tmpStack.pop();
                }
                closedSet.insert(nodeToCheck.id);
                expandNode(&nodeToCheck, 'a');
            }
            
        } else {
            if (pqaStar.top()->getFCost() == pqid.top()->getFCost()) {
                while (pqaStar.top()->getId() != pqid.top()->getId()) {
                    tmpStack.push(pqaStar.top());
                    pqaStar.pop();
                }
                PancakeNode &nodeToCheck = *pqaStar.top();
                bool isGoal = checkGoalNode(&nodeToCheck);
                if (isGoal == true) {
                    printPath(&nodeToCheck);
                    return true;
                } else {
                    pqid.pop();
                    pqaStar.pop();
                    closedSet.insert(nodeToCheck.id);
                    expandNode(&nodeToCheck, 'a');
                    tmpStackSize = tmpStack.size();
                    for (int i = 0; i < tmpStackSize; i++) {
                        pqaStar.push(tmpStack.top());
                        tmpStack.pop();
                    }
                }
            } else {
                while (pqaStar.top()->getFCost() != pqid.top()->getFCost()) {
                    tmpStack.push(pqid.top());
                    pqid.pop();
                }
                PancakeNode &nodeToCheck = *pqid.top();
                bool isGoal = checkGoalNode(&nodeToCheck);
                if (isGoal == true) {
                    printPath(&nodeToCheck);
                    return true;
                } else {
                    pqid.pop();
                    closedSet.insert(nodeToCheck.id);
                    expandNode(&nodeToCheck, 'a');
                    tmpStackSize = tmpStack.size();
                    for (int i = 0; i < tmpStackSize; i++) {
                        pqid.push(tmpStack.top());
                        tmpStack.pop();
                    }
                    while (pqaStar.top()->getId() != nodeToCheck.getId()){
                        tmpStack.push(pqaStar.top());
                        pqaStar.pop();
                    }
                    pqaStar.pop();
                    tmpStackSize = tmpStack.size();
                    for (int i = 0; i < tmpStackSize; i++) {
                        pqaStar.push(tmpStack.top());
                        tmpStack.pop();
                    }
                }
            }
        }
        
        
    }
    
    // no solution found
    return false;
}
