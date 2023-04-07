#include <Windows.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>
#include "geometry.h"
#include "camera.h"
#include "drawing.h"


static int W = 800;
static int H = 500;
static Camera* const CAMERA = &Camera::Get();


void transformToViewport(int& sx, int& sy) {
	sx = sx - W / 2;
	sy = H / 2 - sy;
}


void transformToWindow(int& sx, int& sy) {
	sx = sx + W / 2;
	sy = H / 2 - sy;
}


void displayFunc() {
	// Time display loop
	static const int FPS = 30;
	static const double SPF = 1. / FPS;
	double startTime = clock();

	// Refresh buffer and screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	// Draw elements
	glColor4f(1, 1, 1, 0);
	drawGround(100, 100);

	// Update camera
	CAMERA->drawDirectionCircle();
	CAMERA->step();
	CAMERA->look();

	glutSwapBuffers();

	// Delay roughly according to FPS
	while (clock() - startTime < SPF) {}
}


void keyboardToggleFunc(unsigned char key, int sx, int sy) {
	switch (key) {
	case 'w':
		CAMERA->wasdStates ^= 0b1000;
		break;
	case 'a':
		CAMERA->wasdStates ^= 0b0100;
		break;
	case 's':
		CAMERA->wasdStates ^= 0b0010;
		break;
	case 'd':
		CAMERA->wasdStates ^= 0b0001;
		break;
	default:
		return;
	}
}


void passiveMotionFunc(int sx, int sy) {
	static const double sxMin = 0.05 * W;
	static const double sxMax = 0.10 * W;
	transformToViewport(sx, sy);
	if (sx > -sxMin && sx < sxMin) {
		return;
	}
	if (sx < -sxMax) {
		sx = -sxMax;
	}
	else if (sx > sxMax) {
		sx = sxMax;
	}
	CAMERA->orient(sx, sy);
	transformToWindow(sx, sy);
	glutWarpPointer(sx, sy);
}


int main(int argc, char** argv) {
	// Do initial GLUT setup
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	const int SW = glutGet(GLUT_SCREEN_WIDTH);
	const int SH = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((SW - W) / 2, (SH - H) / 2);
	glutInitWindowSize(W, H);

	// Create window and register functions
	glutCreateWindow("SCAPE");
	glutIdleFunc(displayFunc);
	glutDisplayFunc(displayFunc);
	glutKeyboardFunc(keyboardToggleFunc);
	glutKeyboardUpFunc(keyboardToggleFunc);
	glutPassiveMotionFunc(passiveMotionFunc);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutSetCursor(GLUT_CURSOR_NONE);

	// Intial OpenGL setup
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glEnable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(W / 2, -H / 2,W / 2, H / 2);
	const double ratio = static_cast<double>(W) / H;
	gluPerspective(45, ratio, Camera::R_NEAR, Camera::R_FAR);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Run main loop
	glutMainLoop();
	return 0;
}


