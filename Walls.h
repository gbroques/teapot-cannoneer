#ifndef WALLS_H
#define WALLS_H

#include <GL/glut.h>

class Walls
{
	public:
		static void draw(GLuint list);
		static GLuint getList();
		static void bindTextures();

	private:
		static const GLuint CLOUDS_TEXTURE;
		static const GLuint GRASS_TEXTURE;
		static const GLfloat xOffset;
		static const GLfloat yOffset;
		static const GLfloat zOffset;
		static void drawBackWall();
		static void drawCeiling();
		static void drawLeftWall();
		static void drawRightWall();
		static void drawFloor();
};

#endif