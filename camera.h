#pragma once
#include "geometry.h"


class Camera {
public:
	static Camera& Get();
	void jump();
	void step();
	void orient(double sx, double sy);
	void look();
	void drawDirectionCircle();

	static const double R_NEAR;
	static const double R_FAR;
	static const double DY;

	unsigned short wasdStates;

private:
	Camera();
	~Camera() = default;
	Camera(const Camera& camera) = delete;
	Camera& operator= (const Camera& camera) = delete;

	static Camera singleton;

	Body body;
	double dy;
	double height;
};
