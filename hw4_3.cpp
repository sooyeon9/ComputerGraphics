static bool mouseLeftDown;
static float point[2][2];
void mouseButton(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void timer(int value);
void quad(int a, int b, int c, int d);
static bool R = true;
static bool G = true;
static bool B = true;
static float theda;
bool rot = true;
int r,x_axis=0,y_axis=1,z_axis=0;
float scale = 4.0;

GLfloat vertices[8][3] = {
    {-1,-1,1},{-1,1,1},
{1,1,1},{1,-1,1},{-1,-1,-1},
{-1,1,-1},{1,1,-1},{1,-1,-1} };


GLfloat colors[8][3] = {
    {0,0,1},{0,1,1},
    {1,1,1},{1,0,1},
    {0,0,0},{0,1,0},
    {1,1,0},{1,0,0}
};

void menu(int item)
{
    keyboard((unsigned char)item,0,0);
}

void ChangeSize(int w, int h)
{
    GLfloat aspectRatio;

    if(h==0)
        h=1;

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w/(GLfloat)h;
    if(w<=h)
    {
        gluOrtho2D((float)-1*scale,scale,(float)-1*scale*(float)h/(float)w, scale*(float)h/(float)w);
    }
    else
    {
        gluOrtho2D((float)-1*scale*(float)w/(float)h, scale*(float)w/(float)h,(float)-1*scale,scale);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'q'|'Q':
        exit(0); break;
    case VK_ESCAPE:
        exit(0); break;
    case 1:
        exit(0); break;
    case 2:
        exit(0); break;
    case 'x'|'X':
        {
            x_axis = 1;
            y_axis = 0;
            z_axis = 0;
            break;
        }
    case 'y'|'Y':
        {
            x_axis = 0;
            y_axis = 1;
            z_axis = 0;
            break;
        }
    case 'z'|'Z':
        {
            x_axis = 0;
            y_axis = 0;
            z_axis = 1;
            break;
        }
    case 'p'|'P':
        {
            scale= scale-0.5;
            ChangeSize(500,500);
            break;
        }
    case 'm'|'M':
        {
            scale= scale+0.5;
            ChangeSize(500,500);
            break;
        }
    default:
        break;
    }
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.5,0.5,0.5, 0,0,0, 0,1,0);
    glRotatef(theda, x_axis, y_axis, z_axis);

    quad(0,3,2,1);
    quad(2,3,7,6);
    quad(3,0,4,7);
    quad(1,2,6,5);
    quad(4,5,6,7);
    quad(5,4,0,1);
    glEnd();
    glutSwapBuffers();
}

void quad(int a, int b, int c, int d)
{
    glBegin(GL_QUADS);
    glColor3fv(colors[a]); glVertex3fv(vertices[a]);
    glColor3fv(colors[b]); glVertex3fv(vertices[b]);
    glColor3fv(colors[c]); glVertex3fv(vertices[c]);
    glColor3fv(colors[d]); glVertex3fv(vertices[d]);
}

void mouseButton(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON)
    {
        if(state==GLUT_DOWN)
        {
            if(!mouseLeftDown)
            {
                if(rot)
                    rot=false;
                else
                    rot=true;
            }
        }
        else if(state==GLUT_UP)
        {
            if(mouseLeftDown)
                mouseLeftDown=false;
        }
    }
    else if(button==GLUT_RIGHT_BUTTON)
    {
        if(state==GLUT_DOWN){}
        else if(state==GLUT_UP){}
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
    if(mouseLeftDown)
    {
        double viewport[4];
        glGetDoublev(GL_VIEWPORT,viewport);

        point[1][0] = x/(float)viewport[2]*500;
        point[1][1] = (viewport[3]-y)/(float)viewport[3]*500;
    }
    glutPostRedisplay();
}

void timer(int value)
{
    if(rot)
    {
        theda += 2.0;
        if(theda >= 360.0)
            theda -= 360.0;
    }
    else
    {
        theda -= 2.0;
        if(theda <= 360.0)
            theda += 360.0;
    }
    glutTimerFunc(1000/30, timer, 1);
    glutPostRedisplay();
}

void init(void)
{
    theda = 0.0f;
    glutTimerFunc(10,timer,1);
}

void SetupRc(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("HW4-3");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(1000/30,timer,1);
    glutKeyboardFunc(keyboard);

    glutCreateMenu(menu);
    glutAddMenuEntry("1",1);
    glutAddMenuEntry("2",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();
    SetupRc();
    srand(time(NULL));

    glutMainLoop();

    return 0;
}
