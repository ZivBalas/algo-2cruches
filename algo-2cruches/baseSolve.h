#pragma once
#include <iostream>
#include <utility>
#include "Application.h"
using State = std::pair<int, int>; // מצב מייצג זוג כמויות (כד גדול, כד קטן)

class baseSolve {
public:
    enum Operation {
        FILL_LARGE,
        FILL_SMALL,
        EMPTY_LARGE,
        EMPTY_SMALL,
        TRANSFER_LARGE_TO_SMALL,
        TRANSFER_SMALL_TO_LARGE
    };
   
    baseSolve(int l, int s, int w) : L(l), S(s), W(w) {}
    virtual void run() = 0;
    virtual ~baseSolve() = default;

protected:
    int L, S, W;
};