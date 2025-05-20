#pragma once

#include "baseSolve.h"
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

class solveBFS : public baseSolve {
public:
    solveBFS(int l, int s, int w) : baseSolve(l, s, w) {}
    void run() override;

private:
    vector<vector<pair<State, Operation>>> adjListFlat; // its a vector that contain the vertex , and every vertex contain a list of pairs (state, operation)
    vector<int> distFlat;                                // save the distanse from the start state to every state
    vector<State> parentFlat;                            // save the perent for every state
    vector<Operation> opUsedFlat;                        // save the operation that was used to get to the state

    int index(int large, int small) const { return large * (S + 1) + small; }// make flat vactor from the 2D matrix

    void MakeEmptyGraph();
    void BuildGraph();
    void AddEdge(int large, int small);
    list<pair<State, Operation>> GetAdjList(const State& u);
    bool BFS();
    string operationToString(Operation op);
};
