#pragma once
#include "baseSolve.h"
#include <iostream>
#include <unordered_set>
#include <vector>

class solveHASH : public baseSolve {
public:
    solveHASH(int l, int s, int w) : baseSolve(l, s, w) {}
    void run() override;

private:
    std::vector<std::pair<State, Operation>> calculateAdjList(const State& current);
    std::unordered_set<State> visited;
};
