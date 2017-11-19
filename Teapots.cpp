#include <numeric>
#include "Teapots.h"
#include "CannonBall.h"

const int Teapots::TOTAL_TEAPOTS = 15;

const GLfloat Teapots::radius = 0.05f;

GLfloat Teapots::colors[15][3] = {
	{ 0.96f, 0.26f, 0.21f },  // Red
	{ 0.91f, 0.12f, 0.39f },  // Pink
	{ 0.61f, 0.15f, 0.69f },  // Purple
	{ 0.40f, 0.23f, 0.72f },  // Deep Purple
	{ 0.25f, 0.32f, 0.71f },  // Indigo
	{ 0.13f, 0.59f, 0.95f },  // Blue
	{ 0.01f, 0.66f, 0.96f },  // Light Blue
	{ 0.00f, 0.74f, 0.83f },  // Cyan
	{ 0.00f, 0.59f, 0.53f },  // Teal
	{ 0.30f, 0.69f, 0.31f },  // Green
	{ 0.55f, 0.76f, 0.29f },  // Light Green
	{ 0.80f, 0.86f, 0.22f },  // Lime
	{ 1.00f, 0.92f, 0.23f },  // Yellow
	{ 1.00f, 0.76f, 0.03f },  // Amber
	{ 1.00f, 0.60f, 0.00f }   // Orange
};

std::vector<char> Teapots::isHit(15);
GLfloat Teapots::offset = 0.0f;
GLfloat Teapots::angle  = 0.0f;
std::vector<std::vector<GLfloat>> Teapots::positions(15, std::vector<GLfloat>(3));

/**
* Generates a teapot list for increased performance.
*/
GLuint Teapots::getList()
{
	GLuint teapotList = glGenLists(1);
	glNewList(teapotList, GL_COMPILE);
		glutSolidTeapot(radius);
	glEndList();
	return teapotList;
}


void Teapots::setMaterial()
{
	GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 0.5f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	GLfloat specular[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 75.0f);
}


void Teapots::rotate()
{
	const GLfloat rotateBy = 0.5f;
	angle += rotateBy;
	if (angle == (360.0f - rotateBy)) {
		angle = 0.0f;
	}
}

void Teapots::move()
{
	const GLfloat moveBy = 0.00025f;

	offset += moveBy;

	const GLfloat screenEdge = 1.30f;

	if (offset > screenEdge) {
		offset = -screenEdge;
	}
}

void Teapots::checkForHit(void)
{
	int index = getTeapotHit();

	if (index != -1) {
		isHit[index] = 1;
	}
}

unsigned int Teapots::getNumHit()
{
	return std::accumulate(isHit.begin(), isHit.end(), 0);
}

unsigned int Teapots::getNumLeft()
{
	return TOTAL_TEAPOTS - getNumHit();
}

int Teapots::getTeapotHit() {
	for (int i = 0; i < TOTAL_TEAPOTS; i++) {
		std::vector<GLfloat> diff(3);
		std::vector<GLfloat> cannonBallPosition = CannonBall::getPosition();
		diff[0] = cannonBallPosition[0] - positions[i][0];
		diff[1] = cannonBallPosition[1] - positions[i][1];
		diff[2] = cannonBallPosition[2] - positions[i][2];

		std::vector<GLfloat> square(3);
		square[0] = diff[0] * diff[0];
		square[1] = diff[1] * diff[1];
		square[2] = diff[2] * diff[2];

		GLfloat distance = sqrt(square[0] + square[1] + square[2]);

		if (distance < (CannonBall::radius + radius)) {
			return i;
		}
	}
	return -1;
}

/**
 * Draws all the teapots.
 */
void Teapots::draw(GLuint list) {
	setMaterial();
	GLfloat xPos = -0.5f;
	for (int i = 0; i < TOTAL_TEAPOTS; i++) {
		bool evenRow = (i - 1) % 3 == 0;
		GLfloat yPos = -0.25f + (i % 3 * 0.25f);
		if (i % 3 == 0 && i != 0) {
			xPos += 0.25f;
		}
		GLfloat startingRotationAngle = i * 30.0f;
		positions[i][0] = xPos + (evenRow ? -offset : offset);
		positions[i][1] = yPos;
		positions[i][2] = -1.75f;
		if (!isHit[i]) {
			drawTeapot(list, xPos, yPos, startingRotationAngle, evenRow, colors[i]);
		}
	}
}


/**
 * Draws a teapot.
 *
 * @param[in] list            Teapot list.
 * @param[in] x				  The x position of the teapot.
 * @param[in] y				  The y position of the teapot.
 * @param[in] startingAngle   The starting rotational angle of the teapot.
 * @param[in] evenRow		  Wheter the teapot is in an even or odd row.
 * @param[in] mat			  The material vectors for the teapot.
 */
void Teapots::drawTeapot(GLuint list,
						 GLfloat x,
						 GLfloat y,
						 GLfloat startingAngle,
						 bool evenRow,
						 GLfloat color[3]) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	glPushMatrix();
		glTranslatef(x, y, -1.75f);
		glTranslatef((evenRow ? -offset : offset), 0.0f, 0.0f);
		glRotated(angle, 0, 1, 0);
		glRotated(startingAngle, 0, 1, 0);
		glCallList(list);
	glPopMatrix();
}

void Teapots::reset()
{
	std::fill(isHit.begin(), isHit.end(), 0);
	offset = 0.0f;
}