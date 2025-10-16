#include "utils.h"

vector<point2d> line_dda(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    
    GLfloat dx = x2 - x1;
    GLfloat dy = y2 - y1;

    vector<point2d> P;

    if (dx == 0 && dy == 0) {
        P.push_back({roundof(x1), roundof(y1)});
        return P;
    }

    GLfloat m = (dx != 0) ? dy / dx : 1e10;

    if (m <= 1 && m>=-1) {

        if (x2 < x1) {
            swap(x2, x1);
            swap(y2, y1);
        }

        P.push_back({roundof(x1), roundof(y1)});

        GLfloat x = x1;
        GLfloat y = y1;

        while (x<x2) {
            x += 1.0;
            y += m;
            P.push_back({roundof(x), roundof(y)});
        }
    }
    else {
        if (y2 < y1) {
            swap(y2, y1);
            swap(x2, x1);
        }

        P.push_back({roundof(x1), roundof(y1)});

        GLfloat x = x1;
        GLfloat y = y1;

        while (y<y2) {
            x += 1.0 / m;
            y += 1.0;
            P.push_back({roundof(x), roundof(y)});
        }
    }

    P.push_back({roundof(x2), roundof(y2)});
    return P;
}