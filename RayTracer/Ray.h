#pragma once
#include "Types.h"

class Material;

struct raycastHit_t
{
	float t{ 0 };
	glm::vec3 point;
	glm::vec3 normal;

	Material* material;
};

struct ray_t
{
	glm::vec3 origin;
	glm::vec3 direction;

	ray_t() = default;
	ray_t(const glm::vec3& origin, const glm::vec3& direction) : origin{origin}, direction{direction}{}

	glm::vec3 pointAt(float t) const { return origin + (direction * t); }

};