#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include <utility>
#include <cstdio>
#include <ctime>

#include "shape.h"
#include "text.h"
#include "world.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

clock_t current_time = clock();
clock_t last_time = current_time;
float dt = 0;

std::vector<std::pair<int, int>> robot, room, obstacles;

void init_shapes() {
    robot = shape::make_rectangle(40, 40, 100, 200);
    shape::rotate(robot, 0.3);
    room = shape::make_circle(300, 300, 200);
    obstacles = shape::minkowski_sum(robot, room);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2.5);

    glColor3f(0, 0, 1.0);
    shape::draw(obstacles);

    glColor3f(0, 0, 0);
    shape::draw(room);

    glColor3f(1.0, 0, 0);
    shape::draw(robot);

    char message[50];
    sprintf(message, "dt: %f", dt);
    glColor3f(1.0, 0, 1.0);
    text::print(50, 50, message);

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
    init_shapes();

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