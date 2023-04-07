#include "drawing.h"
#include <Windows.h>
#include <GL/glut.h>
#include "geometry.h"


void drawGround(int nw, int nh) {
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
		glVertex3f(i*gw, 0, -GH/2);
		glVertex3f(i*gw, 0, GH/2);
	}
	for (int i = -nh/2; i <= nh/2; i++) {
		glVertex3f(-GW/2, 0, i*gh);
		glVertex3f(GW/2, 0, i*gh);
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


Enemy::Enemy(Body body)
	: body(body)
{}


void Enemy::step() {
	Vector dpos = this->body.dir;
	dpos = this->body.dp * dpos.unit();
	this->body.pos += dpos;
}


Snowman::Snowman(Body body, double r, double h)
	: Enemy(body), r(r), h(h)
{}


void Snowman::draw() {
	// Save current settings
	float currentLineWidth;
	float currentColor[4];
	glGetFloatv(GL_LINE_WIDTH, &currentLineWidth);
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	
	// Draw body
	const Vector& p = this->body.pos;
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(p.x, p.y+this->r, p.z);
	glutSolidSphere(this->r, SLICES, STACKS);
	glPushMatrix();
	const double c = (this->h - 2 * this->r) / 2;
	glTranslatef(0.0, 2*this->r + c, 0.0);

	// Draw head
	glutSolidSphere(c, SLICES, STACKS);
	
	// Draw eyes
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(0.05, 0.10, 0.18);
	glutSolidSphere(0.05, 10, 10);
	glTranslatef(-0.1, 0.0, 0.0);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();
	
	// Draw nose
	glColor3f(1.0, 0.5, 0.5);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.08, 0.5, 10, 2);
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


Armageddon::Armageddon(Body body, double ri, double ro)
	: Enemy(body), ri(ri), ro(ro)
{}


void Armageddon::draw() {

}