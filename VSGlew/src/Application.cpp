//Andre Sacilotto - 231396
//Para instruções de como controlar leia o README
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "glCustom.h"
#include "imageRGB.h"

#define NUM_TEXTURES 3

GLuint texturas[NUM_TEXTURES];
const char* textureFiles[NUM_TEXTURES]{
    "../Assets/road.rgb",
    "../Assets/towerGlobe.rgb",
    "../Assets/board.rgb",
};

static int rotSpeed = 5;
static int rotX = 45;
static int rotY = 0;

static float moveSpeed = 0.8f;
static float moveX = 0.0f;
static float moveY = 10.0f;
static float moveZ = -50.0f;

void carregar_texturas(void) 
{
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        ImageRgb* img;

        glGenTextures(1, &texturas[i]);
        glBindTexture(GL_TEXTURE_2D, texturas[i]);

        if (!(img = ImageLoad((char*)textureFiles[i]))) {
            fprintf(stderr, "Error reading a texture.\n");
            exit(-1);
        }

        GLenum gluerr = gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img->sizeX, img->sizeY, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)(img->data));
        if (gluerr) {
            fprintf(stderr, "GLULib%s\n", gluErrorString(gluerr));
            exit(-1);
        }
    }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void drawConcrete(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter, GLfloat xSize, GLfloat zSize)
{
    GLfloat mat_concreto_light[] = { 0.3f, 0.3f, 0.3f, 1.0 };
    GLfloat mat_concreto_brilho[] = { 5.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_concreto_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_concreto_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_concreto_brilho);

    glPushMatrix();
    glTranslatef(xCenter, yCenter + .5f, zCenter);
    glScalef(xSize, 1.0f, zSize);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawRunway(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter)
{
    glPushMatrix();
    glTranslatef(xCenter, yCenter + .75f, zCenter);
    glRotatef(90, 1, 0, 0);

    glBindTexture(GL_TEXTURE_2D, texturas[0]);
    glEnable(GL_TEXTURE_2D);
    GLfloat st[4][2] = {
        {0, 0},
        {1, 0},
        {1, 6},
        {0, 6},
    };
    glTexPlane(st, 10, 90);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void drawTerminal(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter)
{
    GLfloat mat_terminal_light[] = { .5f, .5f, .7f, 1.0 };
    GLfloat mat_terminal_brilho[] = { 30.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_terminal_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_terminal_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_terminal_brilho);

    glPushMatrix();
    glTranslatef(xCenter - 10.0f, yCenter + 7.5f, zCenter);
    glScalef(40.0, 15.0, 65.0);
    glutSolidCube(1.0);
    glPopMatrix();

    GLfloat mat_terminal_connection_light[] = { .4f, .6f, .6f, 1.0 };
    GLfloat mat_terminal_connection_brilho[] = { 25.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_terminal_connection_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_terminal_connection_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_terminal_connection_brilho);

    glPushMatrix();
    glTranslatef(xCenter + 20, yCenter + 9.0f, zCenter - 5);
    glScalef(20.0, 8.0, 5.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(xCenter + 20, yCenter + 9.0f, zCenter + 25);
    glScalef(20.0, 8.0, 5.0);
    glutSolidCube(1.0);
    glPopMatrix();

    drawConcrete(xCenter + 20, yCenter, zCenter, 20.0, 60.0);
}

void drawCommandTower(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter)
{
    GLfloat mat_tower_light[] = { .9f, .8f, .25f, 1.0 };
    GLfloat mat_tower_brilho[] = { 100.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_tower_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_tower_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_tower_brilho);

    glPushMatrix();
    glTranslatef(xCenter, yCenter + 30.0f, zCenter);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3, 5, 30, 5, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(xCenter, yCenter + 30.0f, zCenter);

    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    gluQuadricDrawStyle(quad, GLU_FILL);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, GLU_SMOOTH);

    glBindTexture(GL_TEXTURE_2D, texturas[1]);
    glEnable(GL_TEXTURE_2D);
    gluSphere(quad, 10, 8, 8);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawHangar(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter)
{
    GLfloat mat_plane_light[] = { 0.5f, 0.5f, 0.5f, 1.0 };
    GLfloat mat_plane_brilho[] = { 30.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_plane_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_plane_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_plane_brilho);

    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glTranslatef(xCenter - 5.0f, yCenter + 6.0f, zCenter);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 12, 12, 28, 12, 12);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glTranslatef(xCenter - 5.0f, yCenter + 6.0f, zCenter);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(12, 1, 12, 12);
    glPopMatrix();

    drawConcrete(xCenter + 13.0f, yCenter, zCenter, 34.0f, 21.0f);
}

void drawGrass(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter)
{
    GLfloat mat_grass_light[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat mat_grass_brilho[] = { 5.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_grass_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_grass_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_grass_brilho);

    glPushMatrix();
    glColor3f(0.25, .75, .25);
    glTranslatef(xCenter, yCenter, zCenter);
    glScalef(150.0, 1.0, 200.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawPlane(GLfloat xCenter, GLfloat yCenter, GLfloat zCenter)
{
    GLfloat mat_plane_light[] = { 1.0f, 1.0f, 1.0f, 1.0 };
    GLfloat mat_plane_brilho[] = { 100.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_plane_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_plane_light);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_plane_brilho);
    //glColor3f(.6f, .1f, .1f);
    
    // asas
    glPushMatrix();
    glTranslatef(xCenter + 3, yCenter, zCenter);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(10, 7, 2, 3);
    glPopMatrix();

    // corpo
    glPushMatrix();
    glTranslatef(xCenter, yCenter, zCenter);
    glRotatef(90, 0, 1, 0);
    glScalef(1, 1, 2.5);
    gluCylinder(gluNewQuadric(), 2, 2, 4, 8, 8);
    glPopMatrix();

    //tras
    glPushMatrix();
    glTranslatef(xCenter, yCenter, zCenter);
    glRotatef(270, 0, 1, 0);
    glutSolidCone(2, 0, 8, 8);
    glPopMatrix();

    // bico
    glPushMatrix();
    glTranslatef(xCenter + 10, yCenter, zCenter);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(2, 3, 8, 8);
    glPopMatrix();
}

void drawBoard()
{
    glColor3f(0.75f, 0.75f, 0.75f);

    glPushMatrix();
    glTranslatef(5.0f, 4.0f, 0);
    glScalef(4.0f, 6.0f, 4.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, 4.0f, 0);
    glScalef(4.0f, 6.0f, 4.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 10, 0);
    glBindTexture(GL_TEXTURE_2D, texturas[2]);
    glEnable(GL_TEXTURE_2D);
    GLfloat st[4][2] = {
        {0, 0},
        {1, 0},
        {1, 1},
        {0, 1},
    };
    glTexPlane(st, 10, 4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    carregar_texturas();

    GLfloat posicao_luz[] = { 0.0, 3.0, 0.0, 1.0 };
    GLfloat cor_luz[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat cor_luz_amb[] = { 0.3, 0.3, 0.3, 1.0 };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    //glDepthMask(GL_TRUE);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glTranslatef(moveX, moveY, moveZ);
    glRotatef((GLfloat)rotX, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)rotY, 0.0, 1.0, 0.0);

    drawGrass(0.0, 0.0, 0.0);

    drawCommandTower(-10.0, 0.0, -75.0);
    drawTerminal(-25.0, 0.0, -20.0);
    drawPlane(-10.0, 5.0, -5.0);

    drawRunway(25.0, 0.0, 0.0);
    drawRunway(50.0, 0.0, 0.0);

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glRotatef(45, 0, 0, 1);
    drawPlane(25.0, 5.0, 25.0);
    glPopMatrix();

    drawHangar(-25.0, 0.0, 40.0);
    drawPlane(-8.0, 5.0, 40.0);
    drawHangar(-25.0, 0.0, 70.0);

    glPushMatrix();
    glTranslatef(-55, 0, -75);
    glRotatef(45, 0, 1, 0);
    drawBoard();
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        moveY -= moveSpeed;
        break;
    case 's':
        moveY += moveSpeed;
        break;
    case 'a':
        moveX += moveSpeed;
        break;
    case 'd':
        moveX -= moveSpeed;
        break;
    case 'W':
        rotX = (rotX + rotSpeed) % 360;
        break;
    case 'S':
        rotX = (rotX - rotSpeed) % 360;
        break;
    case 'D':
        rotY = (rotY - rotSpeed) % 360;
        break;
    case 'A':
        rotY = (rotY + rotSpeed) % 360;
        break;
    case 'r':
        rotX = 0;
        rotY = 0;
        break;
    case 'R':
        moveX = 0;
        moveY = 0;
        moveZ = 0;
        break;

    case 'u':
        moveSpeed += 1;
        break;
    case 'U':
        moveSpeed -= .5;
        if (moveSpeed < .5)
            moveSpeed = .5;
        break;
    case 'i':
        rotSpeed += 1;
        break;
    case 'I':
        rotSpeed -= 1;
        if (rotSpeed < 1)
            moveSpeed = 1;
        break;
    case 27:  // tecla Esc (encerra o programa)
        exit(0);
    }
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        switch (btn)
        {
        case 3:  //mouse wheel scrolls up
            moveZ += moveSpeed;
            glutPostRedisplay();
            break;
        case 4: //mouse wheel scrolls down
            moveZ -= moveSpeed;
            glutPostRedisplay();
            break;
        }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}