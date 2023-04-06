#include <Windows.h>
#include <GL/glut.h>
#include "geometry.h"


void drawGround() {
	glBegin(GL_QUADS);
		glVertex3f(-100, 0, -100);
		glVertex3f(-100, 0, 100);
		glVertex3f(100, 0, 100);
		glVertex3f(100, 0, -100);
	glEnd();
}


void drawPoint(Vector position, float size) {
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f(position.x, position.y, position.z);
	glEnd();
}