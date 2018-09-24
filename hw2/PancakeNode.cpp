//
//  Pancake.cpp
//  hw2
//
//  Created by Hang Chen on 9/20/18.
//  Copyright © 2018 Hang Chen. All rights reserved.
//

#include "PancakeNode.hpp"

using namespace std;

// constructor 1, only to assign the packages order id of this node
PancakeNode::PancakeNode(int id) {
    this->id = id;
    this->gCost = 0;
    this->hCost = this->getLargestPancakeIdOutOfPlace();    // used to calculate this node's heuristic cost
    this->flipFrom = "";
    this->parent = NULL;
    this->leftChild = NULL;
    this->middleChild = NULL;
    this->rightChild = NULL;
}

// used to clone PancakeNode to form child nodes
PancakeNode::PancakeNode(int id, int gCost) {
    this->id = id;
    this->gCost = gCost;
    this->hCost = this->getLargestPancakeIdOutOfPlace();
    this->flipFrom = "";
    this->parent = NULL;
    this->leftChild = NULL;
    this->middleChild = NULL;
    this->rightChild = NULL;
}

// function used to flip the pancakes and return the resulted pancakes. The parimeter flips is the number of pancakes that are to be fliped. e.g. for id = 3421, if flips = 2, the function returns 3421
void PancakeNode::flip(int flips) {
    
    // get each pancake id among the pile
    string originalId = to_string(this->id);
    int firstPancakeId = this->id % 10;
    this->id /= 10;
    int secondPancakeId = this->id % 10;
    this->id /= 10;
    int thirdPancakeId = this->id % 10;
    this->id /= 10;
    int bottomPancakeId = this->id % 10;
    this->id /= 10;
    
    // flip the numbers, add cost and record the action
    if (flips == 2) {
        this->id = bottomPancakeId * 1000 + thirdPancakeId * 100 + firstPancakeId * 10 + secondPancakeId;
        this->flipFrom = originalId.insert(2, "|");
        this->gCost += 2;
    } else if (flips == 3) {
        this->id = bottomPancakeId * 1000 + firstPancakeId * 100 + secondPancakeId * 10 + thirdPancakeId;
        this->flipFrom = originalId.insert(1, "|");
        this->gCost += 3;
    } else if (flips == 4) {
        this->id = firstPancakeId * 1000 + secondPancakeId * 100 + thirdPancakeId * 10 + bottomPancakeId;
        this->flipFrom = originalId.insert(0, "|");
        this->gCost += 4;
    }
    
    // immediately update the heuristic cost after flipping, used getLargestPancakeIdOutOfPlace() written below
    this->hCost = this->getLargestPancakeIdOutOfPlace();
}

// function used to get the largest pancake id that's still out of place to set the heuristic cost of a certain pancake node
int PancakeNode::getLargestPancakeIdOutOfPlace() {
    
    string idCopy = to_string(this->id);
    
    if (idCopy[0] != '4') {
        return 4;
    } else if (idCopy[1] != '3') {
        return 3;
    } else if (idCopy[2] != '2') {
        return 2;
    } else {
        return 0;
    }

}

// getters and setters

int PancakeNode::getId() {
    return this->id;
}


int PancakeNode::getGCost() {
    return this->gCost;
}

void PancakeNode::setHCost() {
    // the heuristic cost of this pancakes node is the largest ID of the cake that's still out of the place per the instruction
    this->hCost = this->getLargestPancakeIdOutOfPlace();
}

int PancakeNode::getHCost() {
    return this->hCost;
}

int PancakeNode::getFCost() {
    return this->hCost + this->gCost;
}
