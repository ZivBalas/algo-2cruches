#pragma once
#include "baseSolve.h"
class Application {
private:
	int L; //large jug
	int S; //small jug
	int W; //water needed
	int version;
	bool measureTime;

public:
	void start();
};