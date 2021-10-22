#include "Tracer.h"

void Tracer::Trace(const ColorBuffer& colorBuffer)
{
	for (int y = 0; y < colorBuffer.height; y++)
	{
		for (int x = 0; x < colorBuffer.width; x++)
		{
			glm::vec2 point;
			point.x = x / (float) colorBuffer.width;
			point.y = y / (float)colorBuffer.height;

			glm::vec3 direction = glm::vec3{ point, 1 };
			direction = glm::normalize(direction);

			colorBuffer.SetColor(x, y, Vec3ToColor(direction));
		}
	}
}
