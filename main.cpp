#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "points.h"
#include "text.h"
#include "load.h"
#include "delaunay.h"

#define WIN_WIDTH 400
#define WIN_HEIGHT 400

clock_t current_time = clock();
clock_t last_time = current_time;
float dt = 0;

points::point_vector room, robot, obstacles, grid;

void init_shapes() {
    robot = points::rectangle(200, 200, 23, 71);
    points::rotate(robot, 0.45);

    room = load::room_preset();
    grid = points::random(0, 0, WIN_WIDTH, WIN_HEIGHT, 100, 10);
//    grid = points::grid(0, 0, WIN_WIDTH, WIN_HEIGHT, 0.01);
//    obstacles = points::minkowski(robot, room);

    delaunay::triangulate(grid);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2.5);

    points::draw(obstacles, 0, 0, 1);
    points::draw(room, 0, 1, 0);
    points::draw(robot, 1, 0, 0);
    points::draw(grid);

    char message[50];
    sprintf(message, "dt: %f", dt);
    text::print(50, 50, message, 1, 0, 1);

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
    srand(static_cast<unsigned int>(time(nullptr)));

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