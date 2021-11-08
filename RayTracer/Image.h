#pragma once
#include "ColorBuffer.h"

#include <string>
#include <vector>

class Image
{
public:
	Image() = default;
	Image(const std::string& filename, uint8_t alpha = 255);

	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip();

	ColorBuffer colorBuffer;

private:
	friend class Framebuffer;
};