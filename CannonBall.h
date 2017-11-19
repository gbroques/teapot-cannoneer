#pragma once

#include <GL/glut.h>
#include <vector>

class CannonBall
{
	public:
		static const GLfloat radius;
		static GLuint getList();
		static const std::vector<GLfloat> getPosition();
		static void draw(GLuint list, GLfloat cannonYaw, GLfloat cannonPitch);
		static void setMove(bool move);
		static const bool isMoving();
		static void move();

	private:
		static const std::vector<GLfloat> initialPosition;
		static std::vector<GLfloat> position;
		static GLfloat cannonBallZ;
		static bool shouldMove;
};

