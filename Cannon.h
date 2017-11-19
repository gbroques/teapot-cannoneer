#pragma once

#include <GL/glut.h>
#include <vector>

class Cannon
{
	public:
		static GLuint getList();
		static void draw(GLuint list);
		static const GLfloat getYaw();
		static const GLfloat getPitch();
		static void moveRight();
		static void moveLeft();
		static void moveUp();
		static void moveDown();

	private:
		static const GLfloat moveBy;
		static const GLfloat yawBound;
		static const GLfloat pitchUpperBound;
		static const GLfloat pitchLowerBound;
		static GLfloat pitch;
		static GLfloat yaw;
		static void setMaterial();
};

