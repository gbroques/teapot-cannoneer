#pragma once

#include <GL/glut.h>
#include <vector>

class Teapots
{
	public:
		static const int TOTAL_TEAPOTS;
		static GLuint getList();
		static void draw(GLuint list);
		static void reset();
		static void setMaterial();
		static void rotate();
		static void move();
		static void checkForHit();
		static unsigned int getNumHit();
		static unsigned int getNumLeft();

	private:
		static const GLfloat radius;
		static GLfloat colors[15][3];
		static std::vector<char> isHit;
		static GLfloat offset;
		static GLfloat angle;
		static std::vector<std::vector<GLfloat>> positions;
		static void drawTeapot(GLuint list, GLfloat x, GLfloat y, GLfloat startingAngle, bool evenRow, GLfloat color[3]);
		static int getTeapotHit();
};

