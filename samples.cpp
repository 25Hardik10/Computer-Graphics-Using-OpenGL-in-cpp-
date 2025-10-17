#include "utils.h"

void rotating_cube() {
    vector<point3d> vertices = {
        {-500,500,500},
        {500,500,500},
        {500,-500,500},
        {-500,-500,500},
        {-500,500,-500},
        {500,500,-500},
        {500,-500,-500},
        {-500,-500,-500}
    };

    vector<vector<vector<GLfloat>>> vertices_homo = _3dtohomo(vertices, 1);

    point3d camera = { 0,0,1200 };
    point3d pup = { 0, 100, 1200 };
    point3d coi = { 0,0,0 };
    GLfloat d = 400;

    while (true) {
        glClear(GL_COLOR_BUFFER_BIT);
        vector<vector<GLfloat>> R = rotate3dyhomo(0.1);
        for (vector<vector<GLfloat>>& it : vertices_homo) {
            it = matrixmultiplication(R, it);
        }
        vector<point3d> vertices_3d = homoto3d(perspective_projection(d, camera_transform(camera, pup, coi, vertices_homo)));
        vector<point2d> vertices_2d;
        for (point3d& it : vertices_3d) {
            vertices_2d.push_back({ it.x, it.y });
        }
        vector<pixel> points = verticestocube(vertices_2d);
        plot2d(points);
    }
}