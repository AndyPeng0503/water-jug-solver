# Water Jug Solver (C++)

This project implements a simple solver for the classic Water Jug Problem using a state-space search approach.  
Given two jugs with capacities A and B, and a goal amount N, the program finds a sequence of actions to measure exactly N units of water.
The solver uses a priority-based search to keep track of the lowest-cost path and reconstructs the final sequence of steps.

## Features
- Models all valid jug operations: fill, empty, and pour.
- Uses a cost-based search to find the minimum-cost solution.
- Automatically reconstructs and prints the sequence of actions.
- Includes simple test cases in `main.cpp`.

## How to Build
```bash
g++ -std=c++11 Jug.cpp main.cpp -o jug
