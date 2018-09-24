# pancakes_ai_algorithms

Four searching algorithms -

<ul>
<li>depth first search</li>
<li>uniform cost search</li>
<li>greedy search</li>
<li>A* search</li>
</ul>

for the classic pancakes order problem written in C++.

This repo contains 5 program files and a output program, which are

PancakeNode.hpp
PancakeNode.cpp
PancakeGraph.hpp
PancakeGraph.cpp
main.cpp
PancakeAlgo

The PancakeNode file specifies the pancake node format for the pancake graph. A pancake node has the fields of the pancake order, and the corresponding g cost and h cost. The graph will build with the algorithm by adding nodes to the path and will try to find the path to the goal node specified in the PancakeGraph class.

The program utilizes the C++ built-in structures unordered_set, priority_queue and stack as the helping data structures.

Each file is very well commented. Please open each file for a detailed explanation of the code.

<h2>Sample Input and Output</h2>
4132g
4|132 g=0, h=3
42|31 g=3, h=3
4|213 g=5, h=3
43|12 g=8, h=2
4321 g=10, h=0
