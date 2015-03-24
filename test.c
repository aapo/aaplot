/*Simple test
gcc -lGL test.c

or use #include <GL/glut.h>
and gcc -lGL -lglut test.c
*/

/* Windows needs #include <windows.h> */
#include <GL/gl.h>

//#include <GL/glut.h>
#include "aaglut.h"

void build(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex3f (-1.0, -1.0, 0.0);
        glVertex3f (1.0, -1.0, 0.0);
        glVertex3f (0.0, 1.0, 0.0);
    glEnd();

    glFlush();
}


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Title");
    init();
    glutDisplayFunc( build );
    glutMainLoop();
    return 0;
}
