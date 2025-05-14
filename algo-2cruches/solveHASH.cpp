#include "solveHASH.h"
#include <iostream>
#include <queue>
using namespace std;

void solveHASH::run() {
    cout << "Running solveHASH (Optimized Hash BFS)..." << endl;
    State start = { 0, 0 };
    queue<pair<State, vector<baseSolve::Operation>>> q;
    q.push(make_pair(start, vector<baseSolve::Operation>()));
    visited.insert(start);

    while (!q.empty()) {
        pair<State, vector<baseSolve::Operation>> front = q.front();
        q.pop();
        State current = front.first;
        vector<baseSolve::Operation> path = front.second;

        if (current.large == W && current.small == 0) {
            cout << "Number of operations: " << path.size() << endl;
            for (int i = 0; i < path.size(); ++i) {
                cout << i + 1 << ". ";
                switch (path[i]) {
                case FILL_LARGE: cout << "Fill large jug"; break;
                case FILL_SMALL: cout << "Fill small jug"; break;
                case EMPTY_LARGE: cout << "Empty large jug"; break;
                case EMPTY_SMALL: cout << "Empty small jug"; break;
                case TRANSFER_LARGE_TO_SMALL: cout << "Transfer large to small"; break;
                case TRANSFER_SMALL_TO_LARGE: cout << "Transfer small to large"; break;
                }
                cout << endl;
            }
            return;
        }

        vector<pair<State, baseSolve::Operation>> neighbors = calculateAdjList(current);
        for (const auto& pair : neighbors) {
            State neighbor = pair.first;
            baseSolve::Operation op = pair.second;

            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                vector<baseSolve::Operation> newPath = path;
                newPath.push_back(op);
                q.push(make_pair(neighbor, newPath));
            }
        }
    }

    cout << "No solution." << endl;
}

std::vector<std::pair<State, baseSolve::Operation>> solveHASH::calculateAdjList(const State& current) {
    vector<pair<State, baseSolve::Operation>> neighbors;
    int large = current.large;
    int small = current.small;

    if (large < L)
        neighbors.push_back({ {L, small}, FILL_LARGE });
    if (small < S)
        neighbors.push_back({ {large, S}, FILL_SMALL });
    if (large > 0)
        neighbors.push_back({ {0, small}, EMPTY_LARGE });
    if (small > 0)
        neighbors.push_back({ {large, 0}, EMPTY_SMALL });
    if (large > 0 && small < S) {
        int pour = min(large, S - small);
        neighbors.push_back({ {large - pour, small + pour}, TRANSFER_LARGE_TO_SMALL });
    }
    if (small > 0 && large < L) {
        int pour = min(small, L - large);
        neighbors.push_back({ {large + pour, small - pour}, TRANSFER_SMALL_TO_LARGE });
    }

    return neighbors;
}
