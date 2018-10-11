#include "text.h"

#include <GL/glut.h>
#include <cstring>

void text::print(float x, float y, const char *string, GLfloat r, GLfloat g, GLfloat b) {
    glRasterPos2f(x, y);
    glColor3f(r, g, b);
    for (size_t i = 0; i < strlen(string); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}
