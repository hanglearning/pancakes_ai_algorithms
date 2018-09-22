//
//  Pancake.cpp
//  hw2
//
//  Created by Hang Chen on 9/20/18.
//  Copyright © 2018 Hang Chen. All rights reserved.
//

#include "PancakeNode.hpp"

using namespace std;


PancakeNode::PancakeNode(int id) {
    this->id = id;
    this->gCost = 0;
    this->hCost = 0;
    this->flipFrom = "";
    this->parent = NULL;
    this->leftChild = NULL;
    this->middleChild = NULL;
    this->rightChild = NULL;
}

// function used to flip the pancakes and return the resulted pancakes. The parimeter flips is the number of pancakes that are to be fliped. e.g. for id = 3421, if flips = 2, the function returns 3421
void PancakeNode::flip(int flips) {
    string originalId = to_string(this->id);
    int firstPancakeId = this->id % 10;
    this->id /= 10;
    int secondPancakeId = this->id % 10;
    this->id /= 10;
    int thirdPancakeId = this->id % 10;
    this->id /= 10;
    int bottomPancakeId = this->id % 10;
    this->id /= 10;
    
    if (flips == 2) {
        this->id = bottomPancakeId * 1000 + thirdPancakeId * 100 + firstPancakeId * 10 + secondPancakeId;
        this->flipFrom = originalId.insert(2, "|");
        this->gCost += 2;
    } else if (flips == 3) {
        this->id = bottomPancakeId * 1000 + firstPancakeId * 100 + secondPancakeId * 10 + thirdPancakeId;
        this->flipFrom = originalId.insert(3, "|");
        this->gCost += 3;
    } else if (flips == 4) {
        this->id = firstPancakeId * 1000 + secondPancakeId * 100 + thirdPancakeId * 10 + bottomPancakeId;
        this->flipFrom = originalId.append("|");
        this->gCost += 4;
    }
    this->hCost = this->getLargestPancakeId();
}

// function used to get the largest pancake id that's still out of place to set the heuristic cost of a certain pancake node
int PancakeNode::getLargestPancakeId() {
    // http://www.cplusplus.com/forum/beginner/36015/
    int maxId = 0;
    int remainder = 0;
    int idCopy = this->id;
    // gradual 10 division algorithm
    while (idCopy > 0) {
        remainder = idCopy % 10;
        if (remainder > maxId) {
            maxId = remainder;
        }
        idCopy /= 10;
    }
    return maxId;
}

int PancakeNode::getId() {
    return this->id;
}

//void PancakeNode::setGCost(int gCostArc) {
//    this->gCost = gCostArc + this->parent->gCost;
//};

int PancakeNode::getGCost() {
    return this->gCost;
}

void PancakeNode::setHCost() {
    // the heuristic cost of this pancakes node is the largest ID of the cake that's still out of the place per the instruction
    this->hCost = this->getLargestPancakeId();
}

int PancakeNode::getHCost() {
    return this->hCost;
}
