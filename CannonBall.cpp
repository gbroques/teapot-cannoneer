#include "CannonBall.h"
#include "Cannon.h"

const GLfloat CannonBall::radius = 0.02f;
const std::vector<GLfloat> CannonBall::initialPosition = { 0.0f, -0.40f, -1.15f };
std::vector<GLfloat> CannonBall::position = { 0.0f, 0.0f, 0.0f };
GLfloat CannonBall::cannonBallZ = 0.0f;
bool CannonBall::shouldMove = false;

void CannonBall::draw(GLuint list, GLfloat cannonYaw, GLfloat cannonPitch) {
	GLfloat x = (-cannonYaw   * cannonBallZ) / 70.0f;
	GLfloat y = ( cannonPitch * cannonBallZ) / 25.0f;
	position[0] = x + initialPosition[0];
	position[1] = y + initialPosition[1];
	position[2] = -cannonBallZ + initialPosition[2];

	glPushMatrix();
		glTranslatef(x, y, -cannonBallZ);
		glCallList(list);
	glPopMatrix();
}

void CannonBall::setMove(bool move)
{
	shouldMove = move;
}

const bool CannonBall::isMoving()
{
	return shouldMove;
}

const std::vector<GLfloat> CannonBall::getPosition()
{
	return position;
}

GLuint CannonBall::getList() {
	GLuint cannonBallList = glGenLists(1);
	glNewList(cannonBallList, GL_COMPILE);
		glTranslatef(initialPosition[0], initialPosition[1], initialPosition[2]);
		glutSolidSphere(radius, 32, 32);
	glEndList();
	return cannonBallList;
}

void CannonBall::move()
{
	GLfloat moveBy = 0.0075f;
	if (shouldMove) {
		cannonBallZ += moveBy;
	}

	if (cannonBallZ > 1.5f) {
		shouldMove = false;
		cannonBallZ = 0.0f;
	}
}