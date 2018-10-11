#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include <utility>
#include <cstdio>
#include <ctime>

#include "shape.h"
#include "text.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

clock_t current_time = clock();
clock_t last_time = current_time;
float dt = 0;

auto circle1 = shape::make_rectangle(50, 50);

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2.5);

    char message[50];
    sprintf(message, "dt: %f", dt);
    glColor3f(0, 0, 0);
    text::print(10, 10, message);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIN_WIDTH, 0.0, WIN_HEIGHT, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();
}

void idle() {
    current_time = clock();
    dt = static_cast<float>(current_time - last_time) / CLOCKS_PER_SEC;
    last_time = current_time;
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Robot Navigation");
    
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}