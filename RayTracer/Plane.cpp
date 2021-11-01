#include "Plane.h"

bool Plane::Hit(const ray_t& r, float min, float max, raycastHit_t& hit)
{
	float denominator = dot(r.direction, normal);

	if (abs(denominator) < glm::epsilon<float>()) return false;

	float t = dot(center - r.origin, normal) / denominator;

	if (t < 0) return false;

	if (t >= min && t <= max)
	{
		hit.t = t;
		hit.point = r.pointAt(t);
		hit.normal = normal;
		hit.material = material.get();

		return true;
	}

	return false;
}
