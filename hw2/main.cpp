//
//  main.cpp
//  hw2
//
//  Created by Hang Chen on 9/20/18.
//  Copyright © 2018 Hang Chen. All rights reserved.
//

#include <iostream>
#include <stack>
#include <set>
#include "PancakeNode.hpp"
#include "PancakeGraph.hpp"


using namespace std;

/* the main function will record the user input and extract the starting
 pancake order and the algorithm the user wishes to choose, then perfom
 the corresponding searching algorithm on the pancakes to find the path
 to the goal state - pancakes order 4321 */

int main() {
    
    // taking user input for pancake order and the algorithm
    string userInput;
    cout << "Please enter the pancake order and the algorithm you wish to use" << endl;
    cout << "in the format xxxxA, where xxxx are integers in [1,2,3,4] and A be the algorithm -" << endl;
    cout << "'d', 'u', 'g' and 'a' characters, which refer to the Depth-First (DFS), Uniform-Cost (UCS), Greedy and A* search algorithms respectively." << endl << endl;
    cin >> userInput;
    
    string pancakeOrder = userInput.substr(0,4);
    char algo = userInput[4];
    
    int pancakeOrderID = stoi(pancakeOrder);
    while (!((1234 <= pancakeOrderID) && (pancakeOrderID <= 4321) && (algo == 'd' || algo == 'u' || algo == 'g' || algo == 'a'))) {
        cout << "Please follow the input format and try again: " << endl;
        cin >> userInput;
        pancakeOrder = userInput.substr(0,4);
        pancakeOrderID = stoi(pancakeOrder);
        algo = userInput[4];
    }
    
    // Initialize the pancakes root node and initialize the graph
    PancakeNode *pancakeRoot = new PancakeNode(pancakeOrderID);
    PancakeGraph *pancakeGraph = new PancakeGraph(pancakeRoot);
    
    /* perform algorithm based on user's chioice -
     see the PancakeGraph class for the details
     of the implementation of each algorithm */
    
    switch (algo) {
        // dfs
        case 'd':
            pancakeGraph->dfs();
            break;
        // ucs
        case 'u':
            pancakeGraph->ucs();
            break;
        // greedy
        case 'g':
            pancakeGraph->greedy();
            break;
        // a*
        case 'a':
            pancakeGraph->aStar();
            break;
    }
    
    return 1;

}
