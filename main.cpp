#include "utils.h"

using namespace std;

int x_min = -1000, x_max = 1000, y_min = -1000, y_max = 1000;

static void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(x_min, x_max, y_min, y_max);
    glClear(GL_COLOR_BUFFER_BIT);
}

void lab() {

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Lab");
    init();
    glutDisplayFunc(rotating_cube);
    glutMainLoop();
    return 0;
}