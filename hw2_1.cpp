#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,200.0);
}

void drawLine(){
    int width=rand()%7+1;
    int startX=rand()%200, startY=rand()%200;
    int endX=rand()%200, endY=rand()%200;

    glLineWidth((GLfloat)width);
    glColor3f((GLfloat)startX/200,(GLfloat)startY/200,(GLfloat)endX/200);
    glBegin(GL_LINES);
        glVertex2i(startX,startY);
        glVertex2i(endX,endY);
    glEnd();
}

void drawTriangle(){
    int width=rand()%7+1;
    int startX=rand()%200, startY=rand()%200;
    int endX=rand()%200, endY=rand()%200;

    if(endY%2==1)
        glPolygonMode(GL_FRONT, GL_LINE);
    glLineWidth((GLfloat)width);
    glColor3f((GLfloat)startX/200,(GLfloat)startY/200,(GLfloat)endX/200);
    glBegin(GL_TRIANGLES);
        glVertex2i(startX,startY);
        glVertex2i(endX,endY);
        glVertex2i((endX+startX)%200,(endY+startY)%200);
    glEnd();
}

void drawSquare(){
    int width=rand()%7+1;
    int startX=rand()%200, startY=rand()%200;
    int endX=rand()%200;

    if(rand()%5==3)
        glPolygonMode(GL_BACK,GL_LINE);
    glLineWidth((GLfloat)width);
    glColor3f((GLfloat)startX/200,(GLfloat)startY/200,(GLfloat)endX/200);
    glBegin(GL_POLYGON);
        glVertex2i(startX,startX);
        glVertex2i(startX,startY);
        glVertex2i(startY,startY);
        glVertex2i(startY,startX);

    glEnd();
}

void drawCircle(){
    int width=rand()%7+1;
    int startX=rand()%200, startY=rand()%200;
    int endX=rand()%200, endY=rand()%100;

    if(endY%2==1)
        glPolygonMode(GL_FRONT, GL_LINE);
    glLineWidth((GLfloat)width);
    glColor3f((GLfloat)startX/200,(GLfloat)startY/200,(GLfloat)endX/200);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++){
        double angle = i*3.141592 / 180;
        double x = (double)endY*cos(angle);
        double y = (double)endY*sin(angle);
        glVertex2f(x+startX,y+startY);
    }

    glEnd();
}



void makeFigure(int figureNum)
{
    int i,rnum;
    for(i=0; i<figureNum; i++){
        rnum = rand()%4;

        if(rnum==0)
            drawLine();
        else if(rnum==1)
            drawTriangle();
        else if(rnum==2)
            drawSquare();
        else if(rnum==3)
            drawCircle();
    }
}

void displayFcn()
{
    int figureNum;
    glClear(GL_COLOR_BUFFER_BIT);
    printf("\nEnter the number of figure to drawing\n");
    scanf("%d",&figureNum);
    while(figureNum!=0){
        makeFigure(figureNum);
        glFlush();
        printf("\nEnter the number of figure to drawing\n");
        scanf("%d",&figureNum);
    }
}


int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("An Example OpenGL Program");
    init();
    glutDisplayFunc(displayFcn);
    glutMainLoop();
    return 0;
}
