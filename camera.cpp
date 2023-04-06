#include "camera.h"
#include <GL/glut.h>


int Camera::W = 800;
int Camera::H = 500;
const double Camera::R_NEAR = 1;
const double Camera::R_FAR = 1000;


Camera Camera::singleton;


Camera& Camera::Get() {
	return Camera::singleton;
}


void Camera::step() {
	double deg;
	switch (this->wasdStates) {
	case 0b0000:
		return;
	case 0b0001:
		deg = -90;
		break;
	case 0b0010:
		deg = 180;
		break;
	case 0b0011:
		deg = -135;
		break;
	case 0b0100:
		deg = 90;
		break;
	case 0b0101:
		return;
	case 0b0110:
		deg = 135;
		break;
	case 0b0111:
		deg = 180;
		break;
	case 0b1000:
		deg = 0;
		break;
	case 0b1001:
		deg = -45;
		break;
	case 0b1010:
		return;
	case 0b1011:
		deg = -90;
		break;
	case 0b1100:
		deg = 45;
		break;
	case 0b1101:
		deg = 0;
		break;
	case 0b1110:
		deg = 90;
		break;
	case 0b1111:
		return;
	default:
		return;
	}
	
	// Projection onto xz-plane.
	Vector dpos = this->body.dir.rotate(this->body.rot, deg);
	dpos.y = 0;
	dpos = this->body.dp * dpos.unit();
	this->body.pos += dpos;
	// std::cout << this->body.pos << " ";
	// std::cout << this->body.dir << " ";
	// std::cout << this->body.rot << std::endl;
}


void Camera::drawAxes() {
	// Save current settings
	float currentLineWidth;
	float currentColor[4];
	glGetFloatv(GL_LINE_WIDTH, &currentLineWidth);
	glGetFloatv(GL_CURRENT_COLOR, currentColor);

	// Draw axes
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor4f(1, 0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5, 0, 0);
	glColor4f(0, 1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5, 0);
	glColor4f(0, 0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5);
	glEnd();

	// Restore previous settings
	glLineWidth(currentLineWidth);
	glColor4f(
		currentColor[0],
		currentColor[1],
		currentColor[2],
		currentColor[3]
	);
}


Camera::Camera()
	: wasdStates(0b0000), 
	body(Body(
		Vector(-5, 1, 0),
		Vector(1, 0, 0),
		0.025,
		Vector(0, 1, 0).unit(),
		0,
		NULL
	))
{}


void Camera::look() {
	glLoadIdentity();
	gluLookAt(
		this->body.pos.x, 
		this->body.pos.y, 
		this->body.pos.z,
		this->body.pos.x + this->R_FAR * this->body.dir.x,
		this->body.pos.y + this->R_FAR * this->body.dir.y,
		this->body.pos.z + this->R_FAR * this->body.dir.z,
		this->body.rot.x,
		this->body.rot.y,
		this->body.rot.z
	);
}