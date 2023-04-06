#include "camera.h"
#include <GL/glut.h>


Camera Camera::singleton;


Camera* Camera::Get() {
	static Camera* const p = &Camera::singleton;
	return p;
}


void Camera::look() {
	gluLookAt(
		this->body.pos.x, this->body.pos.y, this->body.pos.z,
		this->body.dir.x, this->body.dir.y, this->body.dir.z,
		this->body.ax.x, this->body.ax.y, this->body.ax.z
	);
}


Camera::Camera()
	: body(Body(
		Vector(-5, 1, 0),
		Vector(1, 0, 0).unit(),
		1,
		Vector(0, 1, 0).unit(),
		1 * DEGREE
	))
{}