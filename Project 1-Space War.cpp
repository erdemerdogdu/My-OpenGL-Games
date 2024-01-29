/*Name: Erdem
Surname: Erdo�du
Student Number: 22103052
Section: 4
Problems: None
Additional Functionalities:

1.Scoreboard

Detailed Explanation: The aim of my game is to hit as many astroids as possible in 20 seconds.
There can be a maximum of 5 meteorites in the same frame in the game,
but the spacecraft has a maximum of 10 lasers, and these lasers become usable again after a while.
After 20 seconds, a scoreboard appears and shows the statistics of what you have done in the game.
In addition, basic statistics such as which keys should be used and the remaining time are shown in the game.*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600

int  winWidth, winHeight, sx = 0, sy = -175, hit = 0, topready = 10, mistar = 0;
double retime = 20.0;
bool start = false, right = false, left = false, wait = false, conti = false, blabla = true, hjk = true;



void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}



typedef struct {
    int x;
    int y;
}laser_t;

typedef struct {
    int x;
    int y;
}astroid_t;

astroid_t ast[5];
laser_t list[10];
int count = 0;


void laser(int* x, int* y)
{

    glColor3f(1, 0, 0);
    glRectf(*x - 6, *y - 8, *x + 6, *y - 23);


    glColor3f(0.0, 0.0, 0.15);
    glRectf(*x - 3, *y - 8, *x + 3, *y - 23);


}
void astroid(int* x, int* y)
{
    glColor3ub(70, 70, 70);
    circle(*x + 12, *y + 12, 12);

    glColor3ub(70, 70, 70);
    circle(*x - 15, *y - 10, 12);

    glColor3ub(80, 80, 80);
    circle(*x, *y, 20);

    glColor3ub(100, 100, 100);
    circle(*x - 5, *y + 5, 10);

    glColor3ub(55, 55, 55);
    circle(*x + 10, *y - 10, 5);

}
void SpaceShip()
{
    glColor3f(0.75, 0.75, 0.75);
    glBegin(GL_POLYGON);
    glVertex2f(sx, sy);
    glVertex2f(sx - 8, sy - 20);
    glVertex2f(sx + 8, sy - 20);
    glEnd();

    glColor3f(0.75, 0.75, 0.75);
    glRectf(sx - 8, sy - 20, sx + 8, sy - 50);

    glColor3f(0.3, 0.3, 0.3);
    glRectf(sx - 5, sy - 22, sx + 5, sy - 38);

    glColor3f(0.75, 0.75, 0.75);
    glBegin(GL_POLYGON);
    glVertex2f(sx + 8, sy - 50);
    glVertex2f(sx + 8, sy - 35);
    glVertex2f(sx + 25, sy - 25);
    glVertex2f(sx + 40, sy - 25);
    glEnd();

    glColor3f(0.75, 0.75, 0.75);
    glBegin(GL_POLYGON);
    glVertex2f(sx - 8, sy - 50);
    glVertex2f(sx - 8, sy - 35);
    glVertex2f(sx - 25, sy - 25);
    glVertex2f(sx - 40, sy - 25);
    glEnd();

    glColor3f(0.75, 0.75, 0.75);
    glBegin(GL_POLYGON);
    glVertex2f(sx - 25, sy - 25);
    glVertex2f(sx - 40, sy - 25);
    glVertex2f(sx - 20, sy + 15);
    glEnd();

    glColor3f(0.75, 0.75, 0.75);
    glBegin(GL_POLYGON);
    glVertex2f(sx + 25, sy - 25);
    glVertex2f(sx + 40, sy - 25);
    glVertex2f(sx + 20, sy + 15);
    glEnd();


    glColor3f(0.45, 0.85, 1);
    glBegin(GL_POLYGON);
    glVertex2f(sx - 6, sy - 50);
    glVertex2f(sx + 6, sy - 50);
    glVertex2f(sx, sy - 65);
    glEnd();



}
void drawallAst()
{
    for (int i = 0; i < 5; i++) {
        astroid(&ast[i].x, &ast[i].y);
    }
}
void drawAlllasers() {
    for (int i = 0; i < count; i++) {
        laser(&list[i % 10].x, &list[i % 10].y);
    }
}
void stat()
{
    glColor3f(0.0, 0.0, 0.0);
    glRectf(-500, -270, 500, -300);

    glColor3f(1, 1, 1);
    vprint(-490, -285, GLUT_BITMAP_9_BY_15, "Remaning Time : %0.2f", retime);

    glColor3f(1, 1, 1);
    vprint(-240, -285, GLUT_BITMAP_9_BY_15, "Total Points : %d", hit * 10);

    glColor3f(1, 1, 1);
    vprint(10, -285, GLUT_BITMAP_9_BY_15, "Ready Laser: %d", topready);

    glColor3f(1, 1, 1);
    vprint(260, -285, GLUT_BITMAP_9_BY_15, "Burst Laser: %d", count);

    if (!start && retime == 0.0)
    {
        glColor3f(1.0, 0.0, 1.0);
        glRectf(-100, 150, 100, -150);

        glColor3f(0.0, 0.0, 0.0);
        glRectf(-95, 145, 95, -145);

        glColor3f(1, 1, 1);
        vprint(-50, 170, GLUT_BITMAP_9_BY_15, "Time is UP");
        vprint(-80, 100, GLUT_BITMAP_9_BY_15, "Scoreboard");
        vprint(-80, 70, GLUT_BITMAP_9_BY_15, "Points: %d", hit * 10);
        vprint(-80, 40, GLUT_BITMAP_9_BY_15, "Fired Laser: %d", count);
        vprint(-80, 10, GLUT_BITMAP_9_BY_15, "H/F rate: %0.2f", hit / double(count));
        vprint(-80, -20, GLUT_BITMAP_9_BY_15, "Total Hit: %d", hit);
        vprint(-80, -50, GLUT_BITMAP_9_BY_15, "Missed Astroid: %d", mistar);
        vprint(-140, -170, GLUT_BITMAP_9_BY_15, "Press <F1> to start to new game");
    }
    else if (!start && retime > 0.0 && retime < 20.0)
    {
        vprint(-25, 30, GLUT_BITMAP_9_BY_15, "Paused");
        vprint(-100, 0, GLUT_BITMAP_9_BY_15, "Press <F1> to continue");

    }
    else if (start)
    {

        vprint(-150, -265, GLUT_BITMAP_8_BY_13, "<Spacebar> Fire, <F1> Pause/Continue");
    }
    else
    {

        vprint(-150, 0, GLUT_BITMAP_9_BY_15, "Press <F1> to start to new game");

    }
}
void display()
{
    glClearColor(0.0, 0.0, 0.15, 0);
    glClear(GL_COLOR_BUFFER_BIT);



    drawAlllasers();
    drawallAst();

    SpaceShip();


    stat();

    glutSwapBuffers();
}


void onKeyDown(unsigned char key, int x, int y)
{
    if (key == 32)
    {
        if (start)
        {
            if (!(list[count % 10].y < 300 && list[count % 10].y >= sy) || hjk)
            {
                if (count > 10)
                    hjk = false;

                list[count % 10].x = sx;
                list[count % 10].y = sy;
                topready--;
                count++;

            }

        }


    }



    // to refresh the window it calls display() function
    glutPostRedisplay();
}


void onSpecialKeyDown(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;

    }
    if (key == GLUT_KEY_F1)
    {
        if (retime == 0.0)
        {
            start = true;
            hit = 0;
            retime = 20.0;
            topready = 10;
            sx = 0;
            sy = -175;
            count = 0;
            mistar = 0;
            blabla = !blabla;
        }
        if (retime <= 20.0 && retime > 0.0)
        {
            start = !start;
        }
    }


    glutPostRedisplay();
}


void onSpecialKeyUp(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;

    }


    glutPostRedisplay();
}

void initialize(astroid_t a[])
{
    for (int l = 0; l < 5; l++)
    {
        a[l].x = rand() % 900 - 450;
        a[l].y = rand() % 200 + 310;

    }


}

double dist(astroid_t p1, laser_t p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}


void onTimer(int v) {

    glutTimerFunc(34, onTimer, 0);

    if (start)
    {
        if (retime > 0)
            retime -= 0.034;

        if (retime < 0)
        {
            retime = 0.0;
            for (int k = 0; k < 10; k++)
            {
                list[k].y = -320;
            }
            for (int t = 0; t < 5; t++)
            {
                ast[t].x = rand() % 900 - 450;
                ast[t].y = rand() % 200 + 320;
            }
            start = false;
        }


        if (left)
        {
            if (sx > -460)
                sx -= 10;
        }
        if (right)
        {
            if (sx < 460)
                sx += 10;
        }

        for (int l = 0; l < 5; l++)
        {
            if (ast[l].y > -350)
                ast[l].y -= 5;

            if (ast[l].y <= -320)
            {
                mistar++;
                ast[l].x = rand() % 900 - 450;
                ast[l].y = rand() % 200 + 320;

            }

        }

        if (count % 10 > 0 || conti)
        {
            conti = true;
            for (int k = 0; k < 10; k++)
            {
                if (k < count && list[k].y >-300 && list[k].y < 300)
                {
                    list[k].y += 10;

                    for (int i = 0; i < 5; i++)
                    {

                        if (dist(ast[i], list[k]) < 20.0)
                        {
                            ast[i].x = rand() % 900 - 450;
                            ast[i].y = rand() % 100 + 320;
                            list[k].y = -320;
                            topready++;
                            hit++;
                        }
                    }


                }
                else
                {
                    if (list[k].y > 300)
                    {
                        list[k].y = -320;

                        topready++;
                    }

                }


            }

        }

        if (conti && list[0].y < 300 && list[0].y >= sy && list[9].y < 300 && list[0].y >= sy)
        {
            wait = true;
        }
        else
        {
            wait = false;
        }
    }



    glutPostRedisplay();
}





void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Space War by Erdem Erdo�du");
    srand(time(NULL));
    initialize(ast);

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutSpecialUpFunc(onSpecialKeyUp);



    // timer event

    glutTimerFunc(34, onTimer, 0);


    glutMainLoop();
}