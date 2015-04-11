#pragma once
#include <chrono>
#include <vector>
#include <iostream>

using namespace std::chrono;
using namespace std;

class Timer
{
	steady_clock::time_point timer, average, total;
	vector<steady_clock::duration> durations;
public:
	void start();
	void stop();
	double getAverage();
	double getTotal();
	void printAverage();
	void printTotal();
	void clear();
};

