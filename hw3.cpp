#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>

GLsizei winWidth=500, winHeight=500;
const GLdouble pi=3.14159;

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
}

void displayCoordinate(){
    glColor3f(1.f,0.f,0.f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(100.0, 0.0, 0.0);
    glVertex3f(-100.0, 0.0, 0.0);
    glEnd();

    glColor3f(0.f,1.f,0.f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0, 100.0, 0.0);
    glVertex3f(0.0, -100.0, 0.0);
    glEnd();

    glColor3f(0.f,0.f,1.f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0, 0.0, 100.0);
    glVertex3f(0.0, 0.0, -100.0);
    glEnd();
}

void displayWireCude()
{
    glClear(GL_COLOR_BUFFER_BIT);
    gluLookAt(5.0,5.0,20.0,5.0,5.0,-20.0,0.0,1.0,0.0);
    displayCoordinate();

    GLint t=1;
    GLfloat x=0.0, y=0.0, a0=0.0, s0=0.5;

    GLfloat v=50;
    GLdouble theta=pi/3, a=30, s=1.1;

    do{
        glPushMatrix();

        glTranslatef(x, y, 0.0);
        glRotatef(a0,1.0,0.0,0.0);
        glColor3f(0.0,0.0,0.0);

        glutWireCube((s0));

        glPopMatrix();

        x=(v*t*cos(theta))/15;
        y=(v*t*sin(theta)-5*t*t)/15;
        a0 = a0+a;
        s0 = s0*s;

        t++;
    }while(y>0);

    glFlush();

}

void winReshapeFcn(GLint newWidth,GLint newHeight)
{
    glViewport(0,0, newWidth,newHeight);
    glMatrixMode(GL_PROJECTION);
    glFrustum(-2.0,2.0,-2.0,2.0,4.0,40.0);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("HW3");

    init();
    glutDisplayFunc(displayWireCude);
    glutReshapeFunc(winReshapeFcn);

    glutMainLoop();

    return 0;
}
