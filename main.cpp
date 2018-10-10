#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include <utility>

#include "shape.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// auto circl1 = shape::make_circle(

void render() {

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glRectf(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH / 2, WIN_HEIGHT / 2);

    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.5);
        glVertex2f(+0.5, +0.0);
        glVertex2f(+0.0, +0.5);
    glEnd();

    glutSwapBuffers();
}

void reshape(int width, int height) {

    glViewport(0, 0, width, height);
    glutPostRedisplay();
}

void loop(int value) {

    
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Robot Navigation");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);

    glutTimerFunc(100, loop, -1);
    glutMainLoop();

    return 0;
}