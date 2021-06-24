#ifndef __IMAGERGB_H__
#define __IMAGERGB_H__
#include<GL/glut.h>

typedef struct {
	unsigned short imagic;
	unsigned short type;
	unsigned short dim;
	unsigned short sizeX, sizeY, sizeZ;
	char name[128];
	unsigned char* data;
} ImageRgb;

ImageRgb* ImageLoad(char*);

#endif