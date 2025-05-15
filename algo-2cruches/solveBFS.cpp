
#include "solveBFS.h"


void solveBFS::MakeEmptyGraph() {
    adjList.clear();
    adjList.resize(L + 1, vector<vector<pair<State, Operation>>>(S + 1));
}

void solveBFS::AddEdge(int large, int small) {
    auto& neighbors = adjList[large][small];
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

void solveBFS::BuildGraph() {
    for (int i = 0; i <= L; ++i)
        for (int j = 0; j <= S; ++j)
            AddEdge(i, j);
}

list<pair<State, baseSolve::Operation>> solveBFS::GetAdjList(const State& u) {
    int large = u.first;
    int small = u.second;
    auto copy = adjList[large][small];
    sort(copy.begin(), copy.end());
    return list<pair<State, Operation>>(copy.begin(), copy.end());
}

string solveBFS::operationToString(Operation op) {
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

bool solveBFS::BFS() {
    dist.assign(L + 1, vector<int>(S + 1, INT_MAX));
    parent.assign(L + 1, vector<State>(S + 1, { -1, -1 }));
    opUsed.assign(L + 1, vector<Operation>(S + 1, FILL_LARGE));
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

        for (const auto& pair : GetAdjList(curr)) {
            State nb = pair.first;
            Operation op = pair.second;

            if (dist[nb.first][nb.second] == INT_MAX) {
                dist[nb.first][nb.second] = dist[curr.first][curr.second] + 1;
                parent[nb.first][nb.second] = curr;
                opUsed[nb.first][nb.second] = op;
                q.push(nb);
            }
        }
    }

    if (!found) {
        cout << "No solution." << endl;
        return false;
    }

    vector<Operation> actions;
    State step = { W, 0 };
    while (!(step.first == 0 && step.second == 0)) {
        State prev = parent[step.first][step.second];
        actions.push_back(opUsed[step.first][step.second]);
        step = prev;
    }

    reverse(actions.begin(), actions.end());

    cout << "Number of operations: " << actions.size() << endl;
    cout << "Operations: "<< endl;
    for (size_t i = 0; i < actions.size(); ++i) {
        cout << i + 1 << ". " << operationToString(actions[i]) << endl;
    }

    return true;
}

void solveBFS::run() {
    MakeEmptyGraph();
    BuildGraph();
    BFS();
}
