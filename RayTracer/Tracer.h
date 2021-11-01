#pragma once
#include "Types.h"
#include "ColorBuffer.h"

class Scene;
class Camera;

class Tracer
{
public:
	void Trace(const ColorBuffer& colorBuffer, Scene* scene, Camera* camera);

public:
	int samples = 100;
};