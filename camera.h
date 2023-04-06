#pragma once
#include "geometry.h"


class Camera {
public:
	static Camera* Get();
	void step();
	void orient();
	void look();

private:
	Camera();
	~Camera() = default;
	Camera(const Camera& camera) = delete;
	Camera& operator= (const Camera& camera) = delete;

	Body body;
	static Camera singleton;
};
