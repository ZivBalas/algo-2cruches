#include "solveBFS.h"

void solveBFS::MakeEmptyGraph() {// initialize the graph
    int total = (L + 1) * (S + 1);
    adjListFlat.clear();
    adjListFlat.resize(total);
    distFlat.assign(total, INT_MAX);
    parentFlat.assign(total, { -1, -1 });
    opUsedFlat.assign(total, FILL_LARGE);
}

void solveBFS::AddEdge(int large, int small) {
    int idx = index(large, small);
    auto& neighbors = adjListFlat[idx];
    neighbors.clear();

    if (large < L) neighbors.emplace_back(State{ L, small }, FILL_LARGE);
    if (small < S) neighbors.emplace_back(State{ large, S }, FILL_SMALL);
    if (large > 0) neighbors.emplace_back(State{ 0, small }, EMPTY_LARGE);
    if (small > 0) neighbors.emplace_back(State{ large, 0 }, EMPTY_SMALL);

    if (small > 0 && large < L) {
        int t = min(L - large, small);
        neighbors.emplace_back(State{ large + t, small - t }, TRANSFER_SMALL_TO_LARGE);
    }
    if (large > 0 && small < S) {
        int t = min(S - small, large);
        neighbors.emplace_back(State{ large - t, small + t }, TRANSFER_LARGE_TO_SMALL);
    }
}

void solveBFS::BuildGraph() {// add the possible edges to the graph
    for (int i = 0; i <= L; ++i)
        for (int j = 0; j <= S; ++j)
            AddEdge(i, j);
}

list<pair<State, baseSolve::Operation>> solveBFS::GetAdjList(const State& u) {
    auto copy = adjListFlat[index(u.first, u.second)];
    sort(copy.begin(), copy.end());
    return list<pair<State, Operation>>(copy.begin(), copy.end());
}

string solveBFS::operationToString(Operation op) {// convert the operation to string
    switch (op) {
    case FILL_LARGE: return "Fill large jug";
    case FILL_SMALL: return "Fill small jug";
    case EMPTY_LARGE: return "Empty large jug";
    case EMPTY_SMALL: return "Empty small jug";
    case TRANSFER_LARGE_TO_SMALL: return "Transfer from large jug to small jug";
    case TRANSFER_SMALL_TO_LARGE: return "Transfer from small jug to large jug";
    default: return "Unknown operation";
    }
}

bool solveBFS::BFS() {// BFS algorithm to find the shortest path
    queue<State> q;
    distFlat[index(0, 0)] = 0;
    q.emplace(0, 0);

    bool found = false;
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        int currIdx = index(curr.first, curr.second);

        if (curr.first == W && curr.second == 0) {
            found = true;
            break;
        }

        for (const auto& pair : GetAdjList(curr)) {
            State nb = pair.first;// pair <int,int>
            Operation op = pair.second;// the operation
            int nbIdx = index(nb.first, nb.second);

            if (distFlat[nbIdx] == INT_MAX) {// if the state is not visited
                distFlat[nbIdx] = distFlat[currIdx] + 1;
                parentFlat[nbIdx] = curr;
                opUsedFlat[nbIdx] = op;
                q.push(nb);
            }
        }
    }

    if (!found) {
        cout << "No solution." << endl;
        return false;
    }

    vector<Operation> actions;// save the step from the end to the beginning
    State step = { W, 0 };
    while (!(step.first == 0 && step.second == 0)) {
        int idx = index(step.first, step.second);
        State prev = parentFlat[idx];
        actions.push_back(opUsedFlat[idx]);
        step = prev;
    }

    reverse(actions.begin(), actions.end());// order the step from the beginning to the end

    cout << "Number of operations: " << actions.size() << endl;// print the answer organize
    cout << "operations:" << endl;
    for (size_t i = 0; i < actions.size(); ++i) {
        cout << i + 1 << ". " << operationToString(actions[i]) << endl;
    }

    return true;
}

void solveBFS::run() {// MAIN LOOP OF THIS SOLVE
    MakeEmptyGraph();
    BuildGraph();
    BFS();
}
