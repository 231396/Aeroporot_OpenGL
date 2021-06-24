#include<stdlib.h>
#include<GL/glut.h>
#include "glCustom.h"

void glTexPlane(GLfloat stPoints[4][2], GLfloat sizeX, GLfloat sizeY)
{
	glBegin(GL_QUADS);
	glTexCoord2fv(stPoints[0]); glVertex2f(-sizeX, -sizeY);
	glTexCoord2fv(stPoints[1]); glVertex2f(sizeX, -sizeY);
	glTexCoord2fv(stPoints[2]); glVertex2f(sizeX, sizeY);
	glTexCoord2fv(stPoints[3]); glVertex2f(-sizeX, sizeY);
	glEnd();
}

void glTexCube(GLfloat size)
{
	size /= 2;
	glBegin(GL_QUADS);
	// Face inferior
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, -size, -size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, size);
	// Face frontal
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);
	// Face superior
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);
	// Face anterior
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, -size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, -size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, -size);
	// Face direita
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, -size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, size);
	// Face esquerda
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);
	glEnd();
}