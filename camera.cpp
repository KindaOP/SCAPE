#include "camera.h"
#include <time.h>
#include <GL/glut.h>


const double Camera::R_NEAR = 1;
const double Camera::R_FAR = 1000;
const double Camera::DY = 0.05;


Camera Camera::singleton;


Camera& Camera::Get() {
	return Camera::singleton;
}


void Camera::jump() {
	static const double interval = 250;
	static double lastTime = 0;
	static int numMidJump = 0;
	if (this->dy==0) {
		lastTime = clock();
		this->dy = this->DY;
		numMidJump = 0;
	}
	else if (numMidJump >= 1) {
		return;
	}
	else if (clock() - lastTime >= interval) {
		lastTime = 0;
		this->dy = this->DY;
		numMidJump++;
	}
}


void Camera::step() {
	double deg = -420;
	switch (this->wasdStates) {
	case 0b0000:
		break;
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
		break;
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
		break;
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
		break;
	default:
		break;
	}
	
	if (deg != -420) {
		Vector dpos = this->body.dir.rotate(this->body.rot, deg);
		dpos.y = 0;
		dpos = this->body.dp * dpos.unit();
		this->body.pos += dpos;
	}

	double& y = this->body.pos.y;
	if (y + this->dy > this->height) {
		y += this->dy;
		this->dy += GY;
	}
	else {
		y = this->height;
		this->dy = 0;
	}
}


void Camera::orient(double sx, double sy) {
	static const double sensitivity = 0.1;
	static const double yMin = sin(-15 * D2R);
	static const double yMax = sin(15 * D2R);
	const Vector vx = cross(this->body.dir, this->body.rot).unit();
	const Vector vy = cross(vx, this->body.dir).unit();
	Vector dir = sx * vx + sy * vy;
	dir *= sensitivity / this->R_FAR;
	dir += this->body.dir;
	if (dir.y < yMin) {
		dir.y = yMin;
	}
	else if (dir.y > yMax) {
		dir.y = yMax;
	}
	this->body.dir = dir.unit();
}


void Camera::look() {
	glLoadIdentity();
	gluLookAt(
		this->body.pos.x,
		this->body.pos.y,
		this->body.pos.z,
		this->body.pos.x + this->body.dir.x,
		this->body.pos.y + this->body.dir.y,
		this->body.pos.z + this->body.dir.z,
		this->body.rot.x,
		this->body.rot.y,
		this->body.rot.z
	);
}


void Camera::drawDirectionCircle() {
	// Save current settings
	float currentLineWidth;
	float currentColor[4];
	glGetFloatv(GL_LINE_WIDTH, &currentLineWidth);
	glGetFloatv(GL_CURRENT_COLOR, currentColor);

	// Draw axes
	const double size = 5 * this->body.pos.y;
	const int pts = 720;
	const double da = 360. / pts;
	const int ppq = pts / 4;
	const Vector& p = this->body.pos;
	const Vector& r = this->body.rot;
	Vector d = Vector(0, 0, size);
	double a = 0;

	glLineWidth(10);
	glPushMatrix();
	glTranslatef(p.x, 0, p.z);
	glBegin(GL_LINE_LOOP);
		Vector ci;
		Vector cf;
		double j = 0;
		for (int i = 0; i < pts; i++) {
			switch (i) {
			case 0*ppq:
				ci = Vector(0, 0, 1);
				cf = Vector(1, 0, 0);
				j = 0;
				break;
			case ppq:
				ci = Vector(1, 0, 0);
				cf = Vector(1, 1, 0);
				j = 0;
				break;
			case 2*ppq:
				ci = Vector(1, 1, 0);
				cf = Vector(0, 1, 0);
				j = 0;
				break;
			case 3*ppq:
				ci = Vector(0, 1, 0);
				cf = Vector(0, 0, 1);
				j = 0;
				break;
			default:
				break;
			}
			const double fi = (ppq - j) / ppq;
			const double ff = j / ppq;
			Vector c = fi * ci + ff * cf;
			glColor4f(c.x, c.y, c.z, 0);
			Vector v = d.rotate(r, a);
			glVertex3f(v.x, v.y, v.z);
			a += da;
			j++;
		}
	glEnd();
	glPopMatrix();

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
		Vector(0, 1, -5),
		Vector(0, 0, 1).unit(),
		0.01,
		Vector(0, 1, 0).unit(),
		0,
		NULL
		)),
	dy(0)
{
	this->height = this->body.pos.y;
}