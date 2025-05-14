#include "baseSolve.h"
#include <iostream>
#include <chrono>
#include "Application.h" 
using namespace std;


baseSolve::baseSolve(int l, int s, int w)
	: L(l), S(s), W(w) {}   

void baseSolve::execute() {
    if (version == 1) {
        solveBFS solver(L, S, W);
        if (measureTime) {
            auto start = chrono::high_resolution_clock::now();
            solver.run();
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            cout << "Function took " << duration.count() << " microseconds." << endl;
        }
        else {
            solver.run();
        }
    }
    else if (version == 2) {
        solveHASH solver(L, S, W);
        if (measureTime) {
            auto start = chrono::high_resolution_clock::now();
            solver.run();
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            cout << "Function took " << duration.count() << " microseconds." << endl;
        }
        else {
            solver.run();
        }
    }
    else {
        cerr << "Invalid version" << endl;
        exit(1);
    }
}
