#pragma once
#include <Color.hpp>

namespace rt{

class Image{
public:
	void savebmp (const char *filename, int w, int h, int dpi, rt::Color* data);
};
}