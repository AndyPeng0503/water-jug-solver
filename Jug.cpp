#include "Jug.h"
#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

struct State {
    int a, b;
};

struct Node {
    int a, b;
    int cost;
    int pa, pb;
    string action;
};

struct NodeComparator {
    bool operator()(const Node& n1, const Node& n2) const {
        return n1.cost > n2.cost;
    }
};

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA)
{
    // just store all input values
}

Jug::~Jug() {}

int Jug::solve(string &solution) {
    solution = "";
    if (cfA <= 0 || cfB <= 0 || ceA <= 0 || ceB <= 0 ||
        cpAB <= 0 || cpBA <= 0 || Ca <= 0 || Ca > Cb || Cb > 1000 || N > Cb) {
        return -1;
    }

    vector<vector<int>> best(Ca + 1, vector<int>(Cb + 1, numeric_limits<int>::max()));          // best[a][b] = minimum cost to reach state (a, b)

    vector<vector<State>> pred(Ca + 1, vector<State>(Cb + 1, {-1, -1}));            // pred[a][b] = previous state

    vector<vector<string>> act(Ca + 1, vector<string>(Cb + 1, ""));         // act[a][b] = action used to reach (a, b)

    priority_queue<Node, vector<Node>, NodeComparator> pq;
    
    best[0][0] = 0;                                 // Start at (0,0) with cost 0
    pq.push({0, 0, 0, -1, -1, ""});
    bool found = false;
    int finalCost = -1;
    int finalA = -1, finalB = -1;
    
    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        
        // Skip if we already found a cheaper way to this state
        if (cur.cost > best[cur.a][cur.b])      
            continue;

        // Check if we reached the goal: B contains N
        if (cur.a == 0 && cur.b == N) {
            found = true;
            finalCost = cur.cost;
            finalA = cur.a;
            finalB = cur.b;
            break;
        }

        // fill a
        if (cur.a < Ca) {
            int newCost = cur.cost + cfA;
            if (newCost < best[Ca][cur.b]) {
                best[Ca][cur.b] = newCost;
                pred[Ca][cur.b] = {cur.a, cur.b};
                act[Ca][cur.b] = "fill A";
                pq.push({Ca, cur.b, newCost, cur.a, cur.b, "fill A"});
            }
        }

        // fill b
        if (cur.b < Cb) {
            int newCost = cur.cost + cfB;
            if (newCost < best[cur.a][Cb]) {
                best[cur.a][Cb] = newCost;
                pred[cur.a][Cb] = {cur.a, cur.b};
                act[cur.a][Cb] = "fill B";
                pq.push({cur.a, Cb, newCost, cur.a, cur.b, "fill B"});
            }
        }

        // empty a
        if (cur.a > 0) {
            int newCost = cur.cost + ceA;
            if (newCost < best[0][cur.b]) {
                best[0][cur.b] = newCost;
                pred[0][cur.b] = {cur.a, cur.b};
                act[0][cur.b] = "empty A";
                pq.push({0, cur.b, newCost, cur.a, cur.b, "empty A"});
            }
        }

        // empty b
        if (cur.b > 0) {
            int newCost = cur.cost + ceB;
            if (newCost < best[cur.a][0]) {
                best[cur.a][0] = newCost;
                pred[cur.a][0] = {cur.a, cur.b};
                act[cur.a][0] = "empty B";
                pq.push({cur.a, 0, newCost, cur.a, cur.b, "empty B"});
            }
        }

        // pour a -> b
        if (cur.a > 0 && cur.b < Cb) {
            int amount = min(cur.a, Cb - cur.b);
            int newA = cur.a - amount;
            int newB = cur.b + amount;
            int newCost = cur.cost + cpAB;
            if (newCost < best[newA][newB]) {
                best[newA][newB] = newCost;
                pred[newA][newB] = {cur.a, cur.b};
                act[newA][newB] = "pour A B";
                pq.push({newA, newB, newCost, cur.a, cur.b, "pour A B"});
            }
        }

        // pour b -> a
        if (cur.b > 0 && cur.a < Ca) {
            int amount = min(cur.b, Ca - cur.a);
            int newA = cur.a + amount;
            int newB = cur.b - amount;
            int newCost = cur.cost + cpBA;
            if (newCost < best[newA][newB]) {
                best[newA][newB] = newCost;
                pred[newA][newB] = {cur.a, cur.b};
                act[newA][newB] = "pour B A";
                pq.push({newA, newB, newCost, cur.a, cur.b, "pour B A"});
            }
        }
    }

    if (!found) {
        solution = "";
        return 0;
    }

    // Reconstruct the path from final state back to (0,0)
    vector<string> steps;
    int curA = finalA, curB = finalB;
    while (!(curA == 0 && curB == 0)) {
        string move = act[curA][curB];
        steps.push_back(move);
        State p = pred[curA][curB];
        curA = p.a;
        curB = p.b;
    }
    reverse(steps.begin(), steps.end());

    stringstream ss;
    for (const auto &step : steps)
        ss << step << "\n";
    ss << "success " << finalCost;
    solution = ss.str();
    
    return 1;
}