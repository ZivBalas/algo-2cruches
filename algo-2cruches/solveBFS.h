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
    vector<vector<vector<State>>> adjList;  // גרף: לכל מצב, רשימת שכנים
    vector<vector<int>> dist;               // מטריצת מרחקים

    void MakeEmptyGraph();
    void BuildGraph();
    void AddEdge(int large, int small);
    list<State> GetAdjList(const State& u);
    bool BFS();
    string getOperationDesc(const State& from, const State& to);
};
