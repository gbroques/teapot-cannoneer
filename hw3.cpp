/**
* @author G Brenden Roques
* @brief  CS4410 Homework #4
* @date   11/30/2017
*
* A game where the player fires cannonballs at flying teapots.
*/

#include <GL/glut.h>
#include <ctime>
#include <string>
#include <vector>
#include "hw3.h"
#include "Cannon.h"
#include "CannonBall.h"
#include "Walls.h"
#include "Teapots.h"

void main(int argc, char **argv)
{
	srand((unsigned int) time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	windowId = glutCreateWindow("Flying Spinning Teapots");
	setupDisplay();
	glutDisplayFunc(displayGame);
	glutSpecialFunc(onSpecialKeypress);
	glutKeyboardFunc(onKeyPress);
	glutIdleFunc(idle);
	glEnable(GL_LIGHTING);  // Enable light source
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);  // For hidden surface removal
	glEnable(GL_NORMALIZE);  // Normalize vectors for proper shading
	glClearColor(0.10f, 0.10f, 0.10f, 0.0f);  // Set background to light gray
	glViewport(0, 0, 640, 480);
	glutMainLoop();
}

void onKeyPress(unsigned char key, int x, int y) {
	if (key == SPACEBAR && !CannonBall::isMoving()) {
		yawWhenFired = Cannon::getYaw();
		pitchWhenFired = Cannon::getPitch();
		CannonBall::setMove(true);
	}

	if (key == 'q' || (isGameOver() && key == 'n')) {
		glutDestroyWindow(windowId);
		exit(0);
	}

	if (isGameOver() && key == 'y') {
		Teapots::reset();
	}
}

/**
 * Sets up the teapot list, cube list, and teapot materials array for display function.
 */
void setupDisplay() {
	teapotList = Teapots::getList();
	Walls::bindTextures();
	wallsList = Walls::getList();
	cannonList = Cannon::getList();
	cannonBallList = CannonBall::getList();
}

/**
 * The flying spinning teapots display function.
 */
void displayGame()
{
	setLight();
	setCamera();
	drawScene();
}

void setLight() {
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 2.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void onSpecialKeypress(int key, int x, int y)
{
	bool isLeftKeyPressed = false;
	bool isRightKeyPressed = false;
	bool isUpKeyPressed = false;
	bool isDownKeyPressed = false;

	switch (key) {
		case GLUT_KEY_LEFT:
			isLeftKeyPressed = true;
			if (!isRightKeyPressed) {
				Cannon::moveLeft();
			}
			break;
		case GLUT_KEY_RIGHT:
			isRightKeyPressed = true;
			if (!isLeftKeyPressed) {
				Cannon::moveRight();
			}
			break;
		case GLUT_KEY_UP:
			isUpKeyPressed = true;
			if (!isDownKeyPressed) {
				Cannon::moveUp();
			}
			break;
		case GLUT_KEY_DOWN:
			isDownKeyPressed = true;
			if (!isUpKeyPressed) {
				Cannon::moveDown();
			}
			break;
	}
}

void setCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 4 / 3, 0.1, 50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0.01, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	drawText();

	Teapots::draw(teapotList);

	Walls::draw(wallsList);

	Cannon::draw(cannonList);

	CannonBall::draw(cannonBallList, yawWhenFired, pitchWhenFired);

	glutSwapBuffers();
}

void drawText()
{
	glPushAttrib(GL_CURRENT_BIT);
	glColor4f(0.00f, 0.00f, 0.00f, 0.70f);  // Black text
	glDisable(GL_LIGHTING);

	glRasterPos3f(-0.125f, 0.45f, -1.5f);

	if (!isGameOver()) {
		drawNumTeapotsLeft();
	}
	else {
		drawContinuePrompt();
	}

	glEnable(GL_LIGHTING);
	glPopAttrib();
}

bool isGameOver()
{
	return Teapots::getNumLeft() == 0;
}

void drawNumTeapotsLeft()
{
	std::string teapotsLeft = "Teapots Left: ";
	unsigned int numTeapotsLeft = Teapots::getNumLeft();
	teapotsLeft.append(std::to_string(numTeapotsLeft));
	drawBitmapString(teapotsLeft);
}

void drawContinuePrompt()
{
	drawBitmapString("Continue? (Y/N)");
}

void drawBitmapString(std::string str)
{
	for (auto c : str) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}

/**
 * The idle function responsible for animating the game.
 */
void idle()
{
	Teapots::rotate();

	Teapots::move();

	CannonBall::move();

	Teapots::checkForHit();

	glutPostRedisplay();
}
