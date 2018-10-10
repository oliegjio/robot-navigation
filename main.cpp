#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    glRectf(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH / 2, WIN_HEIGHT / 2);

    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.5);
        glVertex2f(+0.5, +0.0);
        glVertex2f(+0.0, +0.5);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Robot Navigation");

    glutDisplayFunc(renderScene);

    glutMainLoop();

    return 0;
}