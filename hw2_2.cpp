#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>

class wcPt2D{
public:
    GLfloat x,y;
};

typedef GLfloat Matrix3x3[3][3];
Matrix3x3 matComposite;
const GLdouble pi=3.14159;

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
}

void matrix3x3SetIdentity(Matrix3x3 matIdent3x3)
{
    GLint row,col;
    for(row=0;row<3;row++)
        for(col=0;col<3;col++)
            matIdent3x3[row][col]=(row==col);
}

void matrix3x3PreMultiPly(Matrix3x3 m1,Matrix3x3 m2)
{
    GLint row, col;
    Matrix3x3 matTemp;
    for(row=0;row<3;row++)
        for(col=0;col<3;col++)
            matTemp[row][col]=m1[row][0]*m2[0][col] + m1[row][1]*m2[1][col] + m1[row][2]*m2[2][col];

    for(row=0;row<3;row++)
        for(col=0;col<3;col++)
            m2[row][col]=matTemp[row][col];
}
void translate2D(GLfloat tx, GLfloat ty)
{
    Matrix3x3 matTransl;
    matrix3x3SetIdentity(matTransl);

    matTransl[0][2]=tx;
    matTransl[1][2]=ty;

    matrix3x3PreMultiPly(matTransl,matComposite);
}
void rotate2D(wcPt2D pivotPt,GLfloat theta)
{
    Matrix3x3 matRot;
    matrix3x3SetIdentity(matRot);

    matRot[0][0]=cos(theta);
    matRot[0][1]=-sin(theta);
    matRot[0][2]=pivotPt.x*(1-cos(theta))+pivotPt.y*sin(theta);
    matRot[1][0] = sin(theta);
    matRot[1][1]=cos(theta);
    matRot[1][2]=pivotPt.y*(1-cos(theta))-pivotPt.x*sin(theta);

    matrix3x3PreMultiPly(matRot,matComposite);
}
void scale2D(GLfloat sx,GLfloat sy, wcPt2D fixedPt)
{
    Matrix3x3 matScale;
    matrix3x3SetIdentity(matScale);

    matScale[0][0]=sx;
    matScale[0][2]=(1-sx)*fixedPt.x;
    matScale[1][1] = sy;
    matScale[1][2]=(1-sy)*fixedPt.y;

    matrix3x3PreMultiPly(matScale,matComposite);
}
void transformVerts2D(GLint nVerts, wcPt2D* verts)
{
    GLint k;
    GLfloat temp;
    for(k=0;k<nVerts;k++){
        temp=matComposite[0][0]*verts[k].x+matComposite[0][1]*verts[k].y+matComposite[0][2];
        verts[k].y=matComposite[1][0]*verts[k].x + matComposite[1][1]*verts[k].y+matComposite[1][2];
        verts[k].x=temp;
    }
}

void triangle(wcPt2D* verts)
{
    GLint k;
    glBegin(GL_TRIANGLES);
    for(k=0;k<3;k++)
        glVertex2f(verts[k].x,verts[k].y);
    glEnd();
}

void displayFcn()
{
    GLint t=1;
    GLfloat x,y, v=110;
    GLdouble seta=pi/2.5, a=-pi/10.0, s=1.07;
    GLint endt;
    endt =v*sin(seta)/5;

    GLint nVerts=3;
    wcPt2D verts[3]={{-5.0,-10.0},{5.0,-10.0},{0.0,10.0}};
    wcPt2D centroidPt;
    wcPt2D pivPt,fixedPt;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    triangle(verts);

    do{
        GLint k,xSum=0,ySum=0;
        for(k=0;k<nVerts;k++){
            xSum+=verts[k].x;
            ySum+=verts[k].y;
        }
        centroidPt.x=GLfloat(xSum)/GLfloat(nVerts);
        centroidPt.y=GLfloat(ySum)/GLfloat(nVerts);

        pivPt=centroidPt;
        fixedPt=centroidPt;
        matrix3x3SetIdentity(matComposite);

        translate2D((-1)*x, (-1)*y);
        x=v*t*cos(seta);
        y=v*t*sin(seta)-5*t*t;
        translate2D(x,y);

        scale2D(s,s,fixedPt);
        rotate2D(pivPt,a);
        transformVerts2D(nVerts,verts);
        glColor3f(0.0,0.0,1.0);
        triangle(verts);
        glFlush();
        t++;
    }while(t<=endt);

}

void winReshapeFcn(GLint newWidth,GLint newHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20.0,800.0,-150.0,500.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("HW2-2");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
    return 0;
}
