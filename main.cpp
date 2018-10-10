#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5, -0.5, +0.0);
        glVertex3f(+0.5, +0.0, +0.0);
        glVertex3f(+0.0, +0.5, +0.0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Robot Navigation");

    glutDisplayFunc(renderScene);

    glutMainLoop();

    return 0;
}