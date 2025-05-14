#pragma once
#include "baseSolve.h"

class solveBFS : public baseSolve {
public:
    solveBFS(int l, int s, int w) : baseSolve(l, s, w) {};
    void run() override;
};
