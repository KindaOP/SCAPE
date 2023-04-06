#pragma once
#include "geometry.h"


class Camera {
public:
	static Camera& Get();
	void step();
	void orient(Vector ddir);
	void drawAxes();
	void look();

	static int W;
	static int H;
	static const double R_NEAR;
	static const double R_FAR;

	unsigned short wasdStates;

private:
	Camera();
	~Camera() = default;
	Camera(const Camera& camera) = delete;
	Camera& operator= (const Camera& camera) = delete;

	static Camera singleton;

	Body body;
};
