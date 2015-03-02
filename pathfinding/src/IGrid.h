#pragma once

class IGrid
{
public:
	int size_x, size_y;

	template <typename T>
	const T get();
	void set();
	friend std::ostream& operator<<(std::ostream & os, const IGrid& map);
};