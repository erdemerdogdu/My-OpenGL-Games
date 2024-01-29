/*Name: Erdem
Surname: Erdoðdu
Student Number: 22103052
Section: 4
Problems: None
Additional Functionalities:
Detailed Explantion

You can use the spacebar key to create a new game and spawn a ghost with left mouse click to start the game.

1.Object orientation
After the game starts you have to escape from the ghost and collect points, you can use the arrow keys to move the pacman.
You can change the direction of the pacman with the right-left arrow keys,
and you can move back and forth in the specified direction with the up and down arrow keys.

2.Collecting Points
While escaping from the ghost, you have to collect points by eating the dots that appear on the screen.
There will be at most 10 points on the screen at the same time, 
after eating these points different points will spawn again in different places after a certain period of time.

3.Scoreboard
Once you are caught by the ghost, the game will end and there will be a scoreboard that will show you the statistics you have done throughout the game.
It will show you how long your game is, how many dots you eat and how many points you collect per second on the scoreboard.
To create a game again you can use the spacebar key, and create the ghost with the left click of the mouse to start the game again.

*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "vec.h"

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600
#define D2R 0.0174532
int  winWidth, winHeight;
int pacangle = 0 , pacx=0 , pacy=0;
int cnt = 0;
bool up = false, down = false, left = false, right = false;
bool hamham = true;
bool start = false, show = false, loc = true;;
int count = 0;
double catchtime = 0;
int i = 0;
int hit = 0;
int clox = -100,cloy=200;
vec_t prevPosP;
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
void vertex(int x1,int y1,vec_t *p, double angle) {
    double xp = (x1 * cos(angle) - y1 * sin(angle)) + p->x;
    double yp = (x1 * sin(angle) + y1 * cos(angle)) + p->y;
    glVertex2d(xp, yp);
}
void vertexcircle(int x1, int y1, vec_t* p, int radius,double angle) {
    double xp = (x1 * cos(angle) - y1 * sin(angle)) + p->x;
    double yp = (x1 * sin(angle) + y1 * cos(angle)) + p->y;
    circle(xp, yp,radius);
}
typedef struct {
    vec_t pos;
    float angle;
    vec_t vel;  //velocity
} enemy_t;

typedef struct {
    vec_t pos;
    float angle;
} player_t;

typedef struct {
    vec_t pos;
    unsigned char r, g, b;
    double waittime;
} entity_t;

player_t P = { { 0, 0 }, 0 };
enemy_t  E = { { 0, 400 },0};
entity_t icons[10];

void background()
{
    glColor3ub(255, 255, 255);
    circle(clox,cloy,25);
    circle(clox-25, cloy+10, 15);
    circle(clox+20, cloy, 15);

    circle(clox-50-100, cloy-100-50, 25);
    circle(clox - 25-50-100, cloy + 10-100-50, 15);
    circle(clox + 20-50-100, cloy-100-50, 15);

    circle(clox+150, cloy-20, 25);
    circle(clox - 25+150, cloy + 10-20, 15);
    circle(clox + 20+150, cloy-20, 15);

    circle(clox+300, cloy-200, 25);
    circle(clox - 25+300, cloy + 10-200, 15);
    circle(clox + 20+300, cloy-200, 15);

    circle(clox-100+600, cloy, 25);
    circle(clox - 25-100+600, cloy + 10, 15);
    circle(clox + 20-100+600, cloy, 15);

    circle(clox - 100+500, cloy - 300-150, 25);
    circle(clox - 25 - 100+500, cloy + 10 - 300-150, 15);
    circle(clox + 20 - 100+500, cloy - 300-150, 15);

    circle(clox - 100-200, cloy - 300+50, 25);
    circle(clox - 25 - 100-200, cloy + 10 - 300+50, 15);
    circle(clox + 20 - 100-200, cloy - 300+50, 15);
}
void ghost(enemy_t *e)
{
    double angle2 = e->angle *D2R;

    glColor3ub(229.5, 0,0);
    vertexcircle(0, 0, &E.pos, 25, angle2);
    /*circle(e.pos.x, e.pos.y , 25);*/

    glColor3f(0.9, 0.0, 0.0);
    glBegin(GL_POLYGON);
    vertex(-25, 0, &E.pos, angle2);
    vertex(+25, 0, &E.pos, angle2);
    vertex(+27, -30, &E.pos, angle2);
    vertex(-27, -30, &E.pos, angle2);
    /*glVertex2f(e.pos.x-25, e.pos.y );
    glVertex2f(e.pos.x+25, e.pos.y );
    glVertex2f(e.pos.x+27, e.pos.y-30);
    glVertex2f(e.pos.x-27, e.pos.y-30);*/
    glEnd();

    glColor3ub(0, 178.5, 204);
    vertexcircle(-18,-34, &E.pos, 9, angle2);
   /* circle(e.pos.x-18, e.pos.y-34,9);*/

    glColor3ub(0, 178.5, 204);
    vertexcircle(0, -34, &E.pos, 9, angle2);
   /* circle(e.pos.x , e.pos.y - 34, 9);*/

    glColor3ub(0, 178.5, 204);
    vertexcircle(+18, -34, &E.pos, 9, angle2);
    /*circle(e.pos.x + 18, e.pos.y - 34, 9);*/
    //eyes

    glColor3ub(255, 255, 255);
    vertexcircle(-5, +5, &E.pos, 7, angle2);
    /*circle(e.pos.x-5, e.pos.y+5, 7);*/

    glColor3ub(255, 255, 255);
    vertexcircle(+15, +5, &E.pos, 7, angle2);
    /*circle(e.pos.x+15, e.pos.y+5, 7);*/

    glColor3ub(0, 0, 0);
    vertexcircle(-2, +5, &E.pos, 4, angle2);
   /* circle(e.pos.x-2, e.pos.y+5, 4);*/

    glColor3ub(0, 0, 0);
    vertexcircle(+18, +5, &E.pos, 4, angle2);
   /* circle(e.pos.x+18, e.pos.y + 5, 4);*/
}
void pacman(player_t *p)
{

    double angle = p->angle * D2R;
    

    glColor3ub(255, 255, 0);
    circle(p->pos.x, p->pos.y, 35);
    
    if (hamham)
    {
        glColor3f(0, 0.7, 0.8);
        glBegin(GL_POLYGON);
        vertex(0, 0, &P.pos, angle);
        vertex(37, 20, &P.pos, angle);
        vertex(37, -20, &P.pos, angle);
        glEnd();
    }
   

    glColor3ub(0, 0, 38.25);
    vertexcircle(10 ,20, &P.pos,5,angle);

}
void icon(entity_t a)
{
    glColor3ub(a.r, a.g, a.b);
    circle(a.pos.x, a.pos.y, 5);

}
void stat()
{
    if (!start && count > 0)
    {
        glColor3f(0.0, 0.0, 1.0);
        glRectf(-100, 150, 100, -150);

        glColor3f(0.0, 0.0, 0.0);
        glRectf(-95, 145, 95, -145);

        glColor3f(1, 1, 1);
        vprint(-80, 100, GLUT_BITMAP_9_BY_15, "Scoreboard");
        vprint(-80, 40, GLUT_BITMAP_9_BY_15, "Points: %d", hit);
        vprint(-80, 70, GLUT_BITMAP_9_BY_15, "Catch Time: %0.2f", catchtime);
        vprint(-80, 10, GLUT_BITMAP_9_BY_15, "P/T  Score: %0.1f", hit/ catchtime);
        vprint(-160, -170, GLUT_BITMAP_9_BY_15, "Press <Spacebar> to create the new game");
    }
    else if (!start)
    {
        glColor3f(1, 1, 1);
        vprint(-160, -170, GLUT_BITMAP_9_BY_15, "Press <Spacebar> to create the game");
    }
    if (start && count % 2 == 0)
    {

        glColor3f(1, 1, 1);
        vprint(-190, -110, GLUT_BITMAP_9_BY_15, "You can control the pacman with arrow keys");
        vprint(-310, -140, GLUT_BITMAP_9_BY_15, "When the game starts collect points without getting caught by the ghost");
        vprint(-160, -170, GLUT_BITMAP_9_BY_15, "Press <Left Click> to start the game");
    }
}
void drawAllIcons() {
    for (int k = 0; k < i; k++) {
        icon(icons[k%10]);
    }
}
void display()
{
    glClearColor(0, 0.7, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawAllIcons();
    ghost(&E);
    pacman(&P);
    background();
    stat();
    glutSwapBuffers();
}


void onKeyDown(unsigned char key, int x, int y)
{
    if (key == 32)
    {
        start = true;

    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onClick(int button, int stat, int x, int y)
{
    if (start)
    {
        if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && count % 2 == 0)
        {
            E.pos = { x - winWidth / 2.0 , winHeight / 2.0 - y };
            count++;
            hit = 0;
            catchtime = 0.0;
        }

    }
   
    // to refresh the window it calls display() function
    glutPostRedisplay() ; 
}
void onSpecialKeyDown(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }

    glutPostRedisplay();
}


void onSpecialKeyUp(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    glutPostRedisplay();
}


double dist(vec_t p1, vec_t p2) {
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

void movePlayer(player_t *p, double speed) {
    double dx = speed * cos(p->angle * D2R);
    double dy = speed * sin(p->angle * D2R);
    int oldx = p->pos.x;
    int oldy = p->pos.y;
    p->pos.x = p->pos.x + dx;
    p->pos.y = p->pos.y + dy;
  
}

void turnPlayer(player_t *p, double turn) {

    p->angle+= turn;
    
    if (p->angle < 0)
        p->angle += 360;

    if (p->angle >= 360) 
        p->angle -= 360;
}

void onTimer(int v) {
    glutTimerFunc(34, onTimer, 0);

    if (start)
    {
        if (count %2 ==  1)
        {
            catchtime += 0.034;
        }

        cnt++;

        if (cnt % 5 == 0)
        {
            hamham = !hamham;
            if (!(icons[i % 10].pos.x < 500 && icons[i % 10].pos.x >-500 && icons[i % 10].pos.y <300 && icons[i % 10].pos.y >-300) || loc )
            {
                if (count % 2 == 1)
                {
                    icons[i % 10].pos.x = rand() % 960 - 480;
                    icons[i % 10].pos.y = rand() % 560 - 280;
                    icons[i % 10].r = rand() % 256;
                    icons[i % 10].g = rand() % 256;
                    icons[i % 10].b = rand() % 100;
                    icons[i % 10].waittime = 0.0;

                    i++;
                }
                
               
            }
            
        }

        if (i > 9)
        {
            loc = false;
        }
        

        if (right) {
            turnPlayer(&P, -4);
        }

        // turn the player counter-clockwise direction
        if (left) {
            turnPlayer(&P, 4);
        }

        // move forward
        if (up) {
            prevPosP = P.pos;
            movePlayer(&P, 5);
        }

        //// move backward
        if (down) {
            prevPosP = P.pos;
            movePlayer(&P, -5);
        }

        E.angle = angleV(E.pos) + 90;
        
        // velocity vector from Enemy to Player
        E.vel = mulV(4.4, unitV(subV(P.pos, E.pos)));
       
        vec_t prevPosG = E.pos;
        if(count%2==1)
            E.pos = addV(E.pos, E.vel); // chase

        if (E.pos.x > 490 || E.pos.x < -490 || E.pos.y > 290 || E.pos.y < -290) {
            E.pos = prevPosG;
        }

        if (P.pos.x > 465 || P.pos.x < -465 || P.pos.y > 265 || P.pos.y < -265) {
            P.pos = prevPosP;
        }

        if (dist(E.pos, P.pos) < 60)
        {
            start = false;
            E.pos.x = 0;
            E.pos.y = 400;
            count++;
            P.pos.x = 0;
            P.pos.y = 0;
            P.angle = 0;
            i = 0;
            loc = true;
           
        }

        for (int a = 0; a < 10; a++)
        {
            if (dist(icons[a].pos, P.pos) < 35)
            {
                icons[a].pos = { 600,0 };
                hit++;
            }
            
            if (icons[a].pos.x > 550 && icons[a].waittime <10.)
            {
                icons[a].waittime += 0.034;
            }
            else if (icons[a].pos.x > 550 && icons[a].waittime >= 10.)
            {
                icons[a].waittime = 0.0;
                icons[a].pos.x = rand() % 960 - 480;
                icons[a].pos.y = rand() % 560 - 280;
                icons[a].r = rand() % 256;
                icons[a].g = rand() % 256;
                icons[a].b = rand() % 100;
            }
        }
        
    }
    glutPostRedisplay();
}





void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pacman by Erdem Erdoðdu");
    srand(time(NULL));
  

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutSpecialUpFunc(onSpecialKeyUp);

    glutMouseFunc(onClick);

    // timer event

    glutTimerFunc(34, onTimer, 0);


    glutMainLoop();
}