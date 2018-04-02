#include "Color.hpp"
namespace rt{

int Color::to_int() const
{
	double sum = red + green + blue;
	double above = sum - 3.0;

	int r = (above > 0 ? (red + above*(red/sum)) : red ) * 255;
	int g = (above > 0 ? (green + above*(green/sum)) : green ) * 255;
	int b = (above > 0 ? (blue + above*(blue/sum)) : blue ) * 255;

	if (r > 255) {r = 255;}
	if (g > 255) {g = 255;}
	if (b > 255) {b = 255;}

	if (r < 0) {r = 0;}
	if (g < 0) {g = 0;}
	if (b < 0) {b = 0;}
	
    return (r << 24) | (g << 16) | (b <<8);
}

Color operator*(const Color& a, double value) {
	return Color{a.red * value, a.green * value, a.blue* value, a.special};
}

Color operator+(const Color& a, const Color& b) {
	return Color{a.red + b.red, a.green + b.green, a.blue + b.blue, a.special};
}

Color operator*(const Color& a, const Color& b) {
	return Color{a.red * b.red, a.green * b.green, a.blue * b.blue, a.special};
}
}
