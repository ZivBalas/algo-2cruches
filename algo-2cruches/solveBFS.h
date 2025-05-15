#pragma once

#include "baseSolve.h"
#include <iostream>
#include "baseSolve.h"
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;


class solveBFS : public baseSolve {
public:
    solveBFS(int l, int s, int w) : baseSolve(l, s, w) {}
    void run() override;

private:
    vector<vector<vector<pair<State, Operation>>>> adjList; // ��� �� ����� ��� ���
    vector<vector<int>> dist;               // ������ ������
    vector<vector<State>> parent;           // �� ��� ���� ��� ���
    vector<vector<Operation>> opUsed;       // ���� ����� ����� ����� ����

    void MakeEmptyGraph();
    void BuildGraph();
    void AddEdge(int large, int small);
    list<pair<State, baseSolve::Operation>> GetAdjList(const State& u);
    bool BFS();
    string operationToString(Operation op);
};
