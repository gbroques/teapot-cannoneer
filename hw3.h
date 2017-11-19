#pragma once

#include <GL/glut.h>

#define SPACEBAR 32

void onKeyPress(unsigned char key, int x, int y);
void setupDisplay();
void displayGame();
void drawScene();
void drawText();
void drawContinuePrompt();
void drawBitmapString(std::string str);
void drawNumTeapotsLeft();
bool isGameOver();
void onSpecialKeypress(int key, int x, int y);
void setCamera();
void setLight();
void idle();

/*--------------------------*
 |         GLOBALS          |
 *--------------------------*/
int windowId;
GLuint teapotList;
GLuint wallsList;
GLuint cannonList;
GLuint cannonBallList;
GLfloat yawWhenFired = 0.0f;
GLfloat pitchWhenFired = 0.0f;