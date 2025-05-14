#pragma once
#include "baseSolve.h"
#include <unordered_set>
#include <vector>
#include <queue>

namespace std {
    template <>
    struct hash<State> {
        size_t operator()(const State& s) const {
            return hash<int>()(s.first) ^ (hash<int>()(s.second) << 1);
        }
    };
}

class solveHASH : public baseSolve {
public:
    solveHASH(int l, int s, int w) : baseSolve(l, s, w) {}
    void run() override;

private:
    std::vector<std::pair<State, Operation>> calculateAdjList(const State& current);
    std::unordered_set<State> visited;
};