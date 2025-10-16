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

void plot2d(vector<point2d> arr) {
    glBegin(GL_POINTS);
    for (point2d& it : arr) {
        glVertex2i(it.x,it.y);
    }
    glEnd();
    glFlush();
}

vector<point2d> verticestopoints2d(vector<vector<GLint>> vertices) {
    vector<point2d> ans;
    int n= vertices.size();
    for (int i = 0; i < n; i++) {
        vector<point2d> edge = line_breshenham(vertices[i][0], vertices[i][1], vertices[(i + 1) % n][0], vertices[(i + 1) % n][1]);
        for (point2d pt : edge) {
            ans.push_back(pt);
        }
    }
    return ans;
}

bool inside_window(GLint x, GLint y, GLint x_min, GLint x_max, GLint y_min, GLint y_max) {
    if (x <= x_max && x >= x_min && y <= y_max && y >= y_min) {
        return true;
    }
    return false;
}

GLfloat mod(point3d pt) {
    return sqrt(pt.x*pt.x+pt.y*pt.y+pt.z*pt.z);
}

point3d cross_prod(point3d a, point3d b) {
    GLfloat x= a.y*b.z-a.z*b.y;
    GLfloat y= b.x*a.z-a.x*b.z;
    GLfloat z= a.x*b.y-b.x*a.y;
    return {x,y,z};
}