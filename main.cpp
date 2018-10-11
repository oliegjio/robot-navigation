#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "shape.h"
#include "text.h"
#include "world.h"
#include "random.h"
#include "random_points.h"

#define WIN_WIDTH 400
#define WIN_HEIGHT 400

clock_t current_time = clock();
clock_t last_time = current_time;
float dt = 0;

vector1 robot, walls, square, rectangle, circle, obstacles, points;
group1 room;

void init_shapes() {
    robot = shape::make_rectangle(200, 200, 23, 71);
    shape::rotate(robot, 0.45);

    room.insert(shape1(world::room_2::make_walls(), color(1, 0, 0)));
    room.insert(shape1(world::room_2::make_square(), color(0, 1, 0)));
    room.insert(shape1(world::room_2::make_rectangle(), color(0, 0, 1)));
    room.insert(shape1(world::room_2::make_circle(), color(1, 0, 1)));

    points = random_points::in_bounds(pair(0, 0), pair(WIN_WIDTH, WIN_HEIGHT), 10000);

    obstacles = shape::minkowski_sum(robot, shape::vectors_from_group1(room));
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2.5);

    shape::draw(obstacles, 0.5, 0.55, 1.0);
    shape::draw(room);
    shape::draw(robot, 1.0, 0, 0);

    glPointSize(1);
    glColor3f(1, 0, 0);
    shape::draw(points);

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
    srand(static_cast<unsigned int>(time(nullptr)));

    init_shapes();

    for (size_t i = 0; i < points.size(); i++) {
        printf(" (%d, %d) ", points[i].first, points[i].second);
    }

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