#include "utils.h"

using namespace std;

int x_min = -960, x_max = 960, y_min = -540, y_max = 540;

static void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(x_min, x_max, y_min, y_max);
    glClear(GL_COLOR_BUFFER_BIT);
}

void test() {

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(550, 350);
    glutInitWindowSize(400, 225);
    glutCreateWindow("Test");

    init();
    glutDisplayFunc(rotating_cube);
    glutMainLoop();
    return 0;
}