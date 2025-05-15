#pragma once
#include "solveBFS.h"
#include "baseSolve.h"
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <string>
#include <climits>
#include <algorithm>


void solveBFS::MakeEmptyGraph() {
    adjList.clear();
    adjList.resize(L + 1, vector<vector<State>>(S + 1));
}

void solveBFS::AddEdge(int large, int small) {
    auto& neighbors = adjList[large][small];
    neighbors.clear();

    if (large < L) neighbors.emplace_back(L, small);
    if (small < S) neighbors.emplace_back(large, S);
    if (large > 0) neighbors.emplace_back(0, small);
    if (small > 0) neighbors.emplace_back(large, 0);

    if (small > 0 && large < L) {
        int t = min(L - large, small);
        neighbors.emplace_back(large + t, small - t);
    }
    if (large > 0 && small < S) {
        int t = min(S - small, large);
        neighbors.emplace_back(large - t, small + t);
    }
}

void solveBFS::BuildGraph() {
    for (int i = 0; i <= L; ++i)
        for (int j = 0; j <= S; ++j)
            AddEdge(i, j);
}

list<State> solveBFS::GetAdjList(const State& u) {
    int large = u.first;
    int small = u.second;
    auto copy = adjList[large][small];
    sort(copy.begin(), copy.end());
    return list<State>(copy.begin(), copy.end());
}

string solveBFS::getOperationDesc(const State& from, const State& to) {
    if (from.first < to.first && from.second == to.second) return "Fill large jug";
    if (from.first == to.first && from.second < to.second) return "Fill small jug";
    if (from.first > to.first && from.second == to.second) return "Empty large jug";
    if (from.first == to.first && from.second > to.second) return "Empty small jug";
    if (from.first > to.first && from.second < to.second) return "Transfer large to small";
    if (from.first < to.first && from.second > to.second) return "Transfer small to large";
    return "Unknown operation";
}

bool solveBFS::BFS() {
    dist.assign(L + 1, vector<int>(S + 1, INT_MAX));
    vector<vector<State>> parent(L + 1, vector<State>(S + 1, { -1, -1 }));
    queue<State> q;

    dist[0][0] = 0;
    q.emplace(0, 0);

    bool found = false;
    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.first == W && curr.second == 0) {
            found = true;
            break;
        }

        for (const auto& nb : GetAdjList(curr)) {
            if (dist[nb.first][nb.second] == INT_MAX) {
                dist[nb.first][nb.second] = dist[curr.first][curr.second] + 1;
                parent[nb.first][nb.second] = curr;
                q.push(nb);
            }
        }
    }

    if (!found) {
        cout << "No solution." << endl;
        return false;
    }

    vector<State> path;
    State step = { W, 0 };
    while (!(step.first == 0 && step.second == 0)) {
        path.push_back(step);
        step = parent[step.first][step.second];
    }
    path.push_back({ 0, 0 });
    reverse(path.begin(), path.end());

    cout << "Number of operations: " << path.size() - 1 << endl;
    for (size_t i = 1; i < path.size(); ++i) {
        cout << i << ". " << getOperationDesc(path[i - 1], path[i]) << endl;
    }

    return true;
}

void solveBFS::run() {
    MakeEmptyGraph();
    BuildGraph();
    BFS();
}
