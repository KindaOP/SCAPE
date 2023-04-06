#include <Windows.h>
#include <GL/glut.h>
#include "geometry.h"


void drawGround(int nw=10, int nh=10) {
	const double GW = 200;
	const double GH = 200;

	// Draw ground
	glBegin(GL_QUADS);
		glVertex3f(-GW/2, 0, -GH/2);
		glVertex3f(GW/2, 0, -GH/2);
		glVertex3f(GW/2, 0, GH/2);
		glVertex3f(-GW/2, 0, GH/2);
	glEnd();
	
	// Save current settings
	float currentLineWidth;
	float currentColor[4];
	glGetFloatv(GL_LINE_WIDTH, &currentLineWidth);
	glGetFloatv(GL_CURRENT_COLOR, currentColor);

	//Draw gridlines
	const double gw = GW / nw;
	const double gh = GH / nh;
	glLineWidth(2);
	glColor4f(0, 0, 0, 0.5);
	glBegin(GL_LINES);
	for (int i = -nw/2; i <= nw/2; i++) {
		glVertex3f(-GH/2, 0, i*gw);
		glVertex3f(GH/2, 0, i*gw);
	}
	for (int i = -nh/2; i <= nh/2; i++) {
		glVertex3f(i*gh, 0, -GW/2);
		glVertex3f(i*gh, 0, GW/2);
	}
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


void drawPoint(Vector position, double size) {
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f(position.x, position.y, position.z);
	glEnd();
}