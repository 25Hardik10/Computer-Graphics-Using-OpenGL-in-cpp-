#include "utils.h"

void swap(GLint& a, GLint& b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void swap(GLfloat& a, GLfloat& b) {
    GLfloat temp = a;
    a = b;
    b = temp;
}

void swap(GLubyte& a, GLubyte& b) {
    a = a^b;
    b = a^b;
    a = a^b;
}

GLint roundof(GLfloat n) {
    if (n - (GLint)n < 0.5) return (GLint)n;
    return (GLint)(n + 1.0);
}

void plot2d(vector<pixel> arr) {
    glBegin(GL_POINTS);
    for (pixel& it : arr) {
        glVertex2i(it.x,it.y);
    }
    glEnd();
    glFlush();
}