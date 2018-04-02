#pragma once

namespace rt{

struct Color{
	double red, green, blue, special;

	int to_int() const;

	friend Color operator*(const Color& a, double value);
	friend Color operator+(const Color& a, const Color& b);
	friend Color operator*(const Color& a, const Color& b);
};

}
