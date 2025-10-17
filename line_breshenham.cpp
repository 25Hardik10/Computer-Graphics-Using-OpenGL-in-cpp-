#include "utils.h"

vector<pixel> line_breshenham(point2d p1, point2d p2) {

    GLint x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;

    GLint dx = x2 - x1;
    GLint dy = y2 - y1;

    vector<pixel> P;

    P.push_back({x1, y1});

    if (abs(dx) >= abs(dy)) {
        // |m| <= 1
        if (x2 < x1) {
            swap(x2, x1);
            swap(y2, y1);
            dx = -dx;
            dy = -dy;
        }
        GLint x = x1;
        GLint y = y1;
        GLint ystep = (dy >= 0) ? 1 : -1;
        dy = abs(dy);
        GLint p = 2 * dy - dx;
        while (x < x2) {
            x += 1;
            if (p < 0) {
                p += 2 * dy;
            }
            else {
                y += ystep;
                p += 2 * dy - 2 * dx;
            }
            P.push_back({x, y});
        }
    }
    else {
        // |m| > 1
        if (y2 < y1) {
            swap(y2, y1);
            swap(x2, x1);
            dx = -dx;
            dy = -dy;
        }
        GLint x = x1;
        GLint y = y1;
        GLint xstep = (dx >= 0) ? 1 : -1; 
        dx = abs(dx);
        GLint p = 2 * dx - dy;
        while (y < y2) {
            y += 1;
            if (p < 0) {
                p += 2 * dx;
            }
            else {
                x += xstep;
                p += 2 * dx - 2 * dy;
            }
            P.push_back({x, y});
        }
    }

    P.push_back({ x2, y2 });
    return P;
}
