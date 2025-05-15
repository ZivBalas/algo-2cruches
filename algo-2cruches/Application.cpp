#include "Application.h"
#include <iostream>
#include <chrono>
#include "solveBFS.h"
#include "solveHASH.h"
using namespace std;

void Application::start() {
    cout << "Enter L S W: ";
    cin >> L >> S >> W;

    if (L <= 0 || S <= 0 || W > L || S >= L) {
        cerr << "Invalid input." << endl;
        return;
    }

    cout << "Enter version (1 or 2): ";
    cin >> version;

    cout << "Measure time? (1 = yes, 0 = no): ";
    cin >> measureTime;

    baseSolve* solver = nullptr;
    if (version == 1) {
        solver = new solveBFS(L, S, W);
    }
    else if (version == 2) {
        solver = new solveHASH(L, S, W);
    }
    else {
        cerr << "Invalid input." << endl;
        exit(1);
    }

    if (measureTime) {
        auto start = chrono::high_resolution_clock::now();
        solver->run();
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Function took " << duration.count() << " microseconds." << endl;
    }
    else {
        solver->run();
    }

    delete solver;
}