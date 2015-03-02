#include "timer.h"

void Timer::start()
{
	timer = steady_clock::now();
}

void Timer::stop()
{
	durations.push_back(steady_clock::now() - timer);
}

double Timer::getAverage()
{
	return getTotal() / durations.size();
}

double Timer::getTotal()
{
	double total = 0;
	for (int i = 0; i < durations.size(); i++)
	{
		total += duration_cast<microseconds>(durations[i]).count();
	}
	return total;
}

void Timer::printAverage()
{
	cout << "Average time taken " << getAverage() << " microseconds" << endl;
}

void Timer::printTotal()
{
	cout << "Total time taken " << getTotal() << " microseconds" << endl;
}