#include <Windows.h>
#include <GL/glut.h>
#include <time.h>
#include "geometry.h"
#include "camera.h"
#include "drawing.h"


static int W = 800;
static int H = 500;
static Vector BG_COLOR(0, 0, 0);
static Vector GND_COLOR(1, 1, 1);
static Camera* CAMERA = Camera::Get();


void displayFunc() {
	// Time display loop
	static const int FPS = 30;
	static const float SPF = 1. / FPS;
	clock_t start_time = clock();

	// Refresh buffer and screen
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BG_COLOR.z, BG_COLOR.y, BG_COLOR.z, 0);

	// Draw elements
	glColor4f(GND_COLOR.x, GND_COLOR.y, GND_COLOR.z, 0);
	drawGround();
	glColor4f(0, 0, 0, 0);
	drawPoint(Vector(0, 0, 0), 10);

	// Swap buffers and display drawing
	glutSwapBuffers();

	// Delay roughly according to FPS
	while (clock() - start_time < SPF) {}
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
	glutCreateWindow("SCAPE - Snowman Escape");
	glutIdleFunc(displayFunc);
	glutDisplayFunc(displayFunc);

	// Do initial OpenGL setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(-W / 2, -H / 2, W / 2, H / 2);
	const float ratio = static_cast<float>(W) / H;
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Run main loop
	CAMERA->look();
	glutMainLoop();
	return 0;
}


