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
        vector<vector<vector<GLfloat>>> ctcube = camera_transform(camera, pup, coi, vertices_homo);
        vector<vector<vector<GLfloat>>> ppcube = perspective_projection(d, ctcube);
        vector<point3d> vertices_3d = homoto3d(ppcube);
        vector<point2d> vertices_2d;
        for (point3d& it : vertices_3d) {
            vertices_2d.push_back({ it.x, it.y });
        }
        vector<pixel> points = verticestocube(vertices_2d);
        plot2d(points);
    }
}

vector<point3d> parametric_sphere(GLfloat r) {
    vector<point3d> ans;
    for (GLfloat theta = 0; theta <= PI; theta += 0.005) {
        for (GLfloat phi = 0.2 * PI; phi <= 0.8 * PI; phi += 0.005) {
            GLfloat x = r * sin(theta) * cos(phi);
            GLfloat z = r * sin(theta) * sin(phi);
            GLfloat y = r * cos(theta);
            ans.push_back({ x,y,z });
        }
    }
    return ans;
}

void sphere() {
    GLfloat radius = 800;
    vector<point3d> points = parametric_sphere(radius);
    point3d source = { 900,900,900 };

    vector<vector<vector<GLfloat>>> points_homo = _3dtohomo(points, 1);

    point3d camera = { 0,0,1200 };
    point3d pup = { 0, 100, 1200 };
    point3d coi = { 0,0,0 };
    GLfloat d = 400;
    vector<vector<vector<GLfloat>>> ctsphere = camera_transform(camera, pup, coi, points_homo);
    vector<vector<vector<GLfloat>>> ppsphere = perspective_projection(d, ctsphere);
    vector<point3d> vertices_3d = homoto3d(ppsphere);

    GLfloat t = 900;
    GLfloat theta = 0;
    while (true) {
        GLfloat x = t * cos(theta);
        GLfloat z = t * sin(theta);
        point3d src = { x,t,z };
        lighting(src, points, camera, vertices_3d, 100, 200, 0.1, 0.8, 0.2, 2, 0, 0.001, 0);
        vector<pixel> pixels;
        for (point3d& it : vertices_3d) {
            pixels.push_back({ roundof(it.x), roundof(it.y), it.r, 0, 0 });
        }
        glClear(GL_COLOR_BUFFER_BIT);
        plot2d(pixels);
        theta += 0.2;
    }
}