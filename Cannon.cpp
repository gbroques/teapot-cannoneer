#include "Cannon.h"

const GLfloat Cannon::moveBy = 1.0f;
const GLfloat Cannon::yawBound = 50.0f;
const GLfloat Cannon::pitchUpperBound = 50.0f;
const GLfloat Cannon::pitchLowerBound = -10.0f;
GLfloat Cannon::pitch = 0.0f;
GLfloat Cannon::yaw   = 0.0f;

void Cannon::draw(GLuint list) {
	setMaterial();
	glPushMatrix();
		glTranslatef(0.0f, -0.40f, -1.15f);
		glRotatef(yaw, 0.0f, 1.0f, 0.0f);
		glRotatef(pitch, 1.0f, 0.0f, 0.0f);
		glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
		glCallList(list);
	glPopMatrix();
}

const GLfloat Cannon::getYaw()
{
	return yaw;
}

const GLfloat Cannon::getPitch()
{
	return pitch;
}

void Cannon::moveRight()
{
	if (yaw > -yawBound) {
		yaw -= moveBy;
	}
}

void Cannon::moveLeft()
{
	if (yaw < yawBound) {
		yaw += moveBy;
	}
}

void Cannon::moveUp()
{
	if (pitch < pitchUpperBound) {
		pitch += moveBy;
	}
}

void Cannon::moveDown()
{
	if (pitch > pitchLowerBound) {
		pitch -= moveBy;
	}
}

GLuint Cannon::getList() {
	GLuint cannonList = glGenLists(1);
	glNewList(cannonList, GL_COMPILE);
		GLUquadricObj* quadratic = gluNewQuadric();
		gluCylinder(quadratic, 0.02f, 0.02f, 0.85f, 32, 32);
	glEndList();
	return cannonList;
}

void Cannon::setMaterial()
{
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[] = { 0.05f, 0.05f, 0.05f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat shininess[] = { 10.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}