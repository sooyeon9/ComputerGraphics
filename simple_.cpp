#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLfloat x1,x2,a=0.01;
void setPixel (GLint xCoord, GLint yCoord)
{
glBegin (GL_POINTS);
glVertex2i(xCoord, yCoord);
glEnd ();
}

void simple_point()
{

    int x=0,y=0;
    setPixel(0,0);
    int p = -49;
    setPixel(0,0);
    void paraboolaPlotPoint(int, int);

    while(x<=50){
        x++;
        if(p<=0)
            p=p+2*x+1;
        else{
            y++;
            p=p+2*x-99;
        }
        paraboolaPlotPoint(x,y);
    }

    p= -199;
    while(50<x&&x<=100){
        y++;
        if(p<0){
            x++;
            p=p+8*x-400;
        }
        else {
            p=p-400;
        }
        paraboolaPlotPoint(x,y);
    }

    /*
    int x,y = 0;

    for(x=0; x>-100; x--){
        int p = -2*x - 49;
        int e = -2*x + 1;
        int ne = -2*x - 99;

        if(p<=0){
            p+=e;
        } else {
            y++;
            p+=ne;
        }
        setPixel(x,y);
    }

    y=0;
    for(x=0; x<100; x++){
        int p = 2*x - 49;
        int e = 2*x + 1;
        int ne = 2*x - 99;

        if(p<=0){
            p+=e;
        } else {
            y++;
            p+=ne;
        }
        setPixel(x,y);
    }

*/

}

void paraboolaPlotPoint(int x,int y){
    setPixel(x,y);
    setPixel(-x,y);
}
void init (void)
{
glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
glMatrixMode (GL_PROJECTION); // Set projection parameters.
gluOrtho2D (-50, 50, -20, 20);
}
void drawCurve( void )
{
glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
glColor3f (0.0, 0.0, 1.0); // Set line segment color to blue.
simple_point();
glFlush ( ); // Process all OpenGL routines as quickly as possible.
}


int main (int argc, char** argv)
{
glutInit (&argc, argv); // Initialize GLUT.
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Set display mode.
glutInitWindowPosition (50, 100); // Set top-left display-window position.
glutInitWindowSize (400, 300); // Set display-window width and height.
glutCreateWindow ("An Example OpenGL Program"); // Create display window.
init ( ); // Execute initialization procedure.
glutDisplayFunc (drawCurve); // Send graphics to display window.
glutMainLoop ( ); // Display everything and wait.

return 0;
}
