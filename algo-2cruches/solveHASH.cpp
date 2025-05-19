#include "solveHASH.h"
#include <iostream>
#include <unordered_set>
using namespace std;

void solveHASH::run() {// here every new vertex we add his adjecent list to the queue in real time.
    vector<pair<State, vector<Operation>>> queue;
    State start = { 0, 0 };
    queue.push_back({ start, {} });
    visited.insert(start);

    while (!queue.empty()) {
        pair<State, vector<Operation>> currentPair = queue.front();
        queue.erase(queue.begin());

        State current = currentPair.first;
        vector<Operation> path = currentPair.second;

        if (current.first == W && current.second == 0) {
            cout << "Number of operations: " << path.size() << endl;
            cout << "Operations: " << endl;
            for (int i = 0; i < path.size(); ++i) {
                cout << i + 1 << ". ";
                switch (path[i]) {
                case FILL_LARGE: cout << "Fill large jug"; break;
                case FILL_SMALL: cout << "Fill small jug"; break;
                case EMPTY_LARGE: cout << "Empty large jug"; break;
                case EMPTY_SMALL: cout << "Empty small jug"; break;
                case TRANSFER_LARGE_TO_SMALL: cout << "Transfer from large jug to small jug"; break;
                case TRANSFER_SMALL_TO_LARGE: cout << "Transfer from small jug to large jug"; break;
                }
                cout << endl;
            }
            return;
        }

        vector<pair<State, Operation>> neighbors = calculateAdjList(current);
        for (const auto& pair : neighbors) {
            State neighbor = pair.first;
            Operation op = pair.second;

            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                vector<Operation> newPath = path;
                newPath.push_back(op);
                queue.push_back({ neighbor, newPath });
            }
        }
    }

    cout << "No solution." << endl;
}

vector<pair<State, baseSolve::Operation>> solveHASH::calculateAdjList(const State& current) {//creat the adjcent list for the curren vertex
    vector<pair<State, Operation>> neighbors;
    int large = current.first;
    int small = current.second;

    if (large < L) neighbors.push_back({ {L, small}, FILL_LARGE });
    if (small < S) neighbors.push_back({ {large, S}, FILL_SMALL });
    if (large > 0) neighbors.push_back({ {0, small}, EMPTY_LARGE });
    if (small > 0) neighbors.push_back({ {large, 0}, EMPTY_SMALL });

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
