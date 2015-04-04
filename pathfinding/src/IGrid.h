#pragma once
#include "Position.h"

class IGrid
{
public:
	int size_x, size_y;

	template <typename T>
	const T get(Position pos);
	template <typename T>
	void set(Position pos, T type);
	friend std::ostream& operator<<(std::ostream & os, const IGrid& map);
};