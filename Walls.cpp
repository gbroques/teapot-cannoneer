#include "Walls.h"
#include "RGBpixmap.h"

const GLuint Walls::CLOUDS_TEXTURE = 2000;
const GLuint Walls::GRASS_TEXTURE  = 2001;
const GLfloat Walls::xOffset = 1.0f;
const GLfloat Walls::yOffset = 0.5f;
const GLfloat Walls::zOffset = 3.0f;

void Walls::draw(GLuint list)
{
	glCallList(list);
}

/**
 * Compiles a list to draw the following five walls:
 *   - Left wall
 *   - Right wall
 *   - Ceiling
 *   - Floor
 *   - Back wall
 */
GLuint Walls::getList()
{
	GLuint list = glGenLists(1);
	glNewList(list, GL_COMPILE);
		glBindTexture(GL_TEXTURE_2D, CLOUDS_TEXTURE);

		drawBackWall();
		drawCeiling();
		drawLeftWall();
		drawRightWall();

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_2D, GRASS_TEXTURE);

		drawFloor();

		glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();
	return list;

}

void Walls::bindTextures()
{
	RGBpixmap cloudsPixmap;
	cloudsPixmap.readBMPFile("clouds.bmp");
	cloudsPixmap.setTexture(CLOUDS_TEXTURE);

	RGBpixmap grassPixmap;
	grassPixmap.readBMPFile("grass.bmp");
	grassPixmap.setTexture(GRASS_TEXTURE);
}

void Walls::drawFloor()
{
	glBegin(GL_QUADS);
		glTexCoord2f(-1.0, -1.0); glVertex3f(-xOffset, -yOffset,  zOffset);
		glTexCoord2f(-1.0,  1.0); glVertex3f(-xOffset, -yOffset, -zOffset);
		glTexCoord2f( 1.0,  1.0); glVertex3f( xOffset, -yOffset, -zOffset);
		glTexCoord2f( 1.0, -1.0); glVertex3f( xOffset, -yOffset,  zOffset);
	glEnd();
}

void Walls::drawRightWall()
{
	glBegin(GL_QUADS); 
		glTexCoord2f(0.0, 0.0); glVertex3f(xOffset, -yOffset,  zOffset);
		glTexCoord2f(0.0, 1.0); glVertex3f(xOffset, -yOffset, -zOffset);
		glTexCoord2f(1.0, 1.0); glVertex3f(xOffset,  yOffset, -zOffset);
		glTexCoord2f(1.0, 0.0); glVertex3f(xOffset,  yOffset,  zOffset);
	glEnd();
}


void Walls::drawCeiling()
{
	glBegin(GL_QUADS); 
		glTexCoord2f(-1.0, -1.0); glVertex3f(-xOffset, yOffset, -zOffset);
		glTexCoord2f(-1.0,  1.0); glVertex3f(-xOffset, yOffset,  zOffset);
		glTexCoord2f( 1.0,  1.0); glVertex3f( xOffset, yOffset,  zOffset);
		glTexCoord2f( 1.0, -1.0); glVertex3f( xOffset, yOffset, -zOffset);
	glEnd();
}

void Walls::drawLeftWall()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-xOffset, -yOffset, -zOffset);
		glTexCoord2f(0.0, 1.0); glVertex3f(-xOffset, -yOffset,  zOffset);
		glTexCoord2f(1.0, 1.0); glVertex3f(-xOffset,  yOffset,  zOffset);
		glTexCoord2f(1.0, 0.0); glVertex3f(-xOffset,  yOffset, -zOffset);
	glEnd();
}


void Walls::drawBackWall()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f( xOffset, -yOffset, -zOffset);
		glTexCoord2f(1.0, 0.0); glVertex3f(-xOffset, -yOffset, -zOffset);
		glTexCoord2f(1.0, 1.0); glVertex3f(-xOffset,  yOffset, -zOffset);
		glTexCoord2f(0.0, 1.0); glVertex3f( xOffset,  yOffset, -zOffset);
	glEnd();
}