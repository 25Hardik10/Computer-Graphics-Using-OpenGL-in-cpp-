#include "utils.h"

vector<point3d> linear_bezier(point3d p0, point3d p1) {
	vector<point3d> ans;
	for (float t = 0; t <= 1; t += 0.01) {
		GLfloat nx = (1 - t) * p0.x + t * p1.x;
		GLfloat ny = (1 - t) * p0.y + t * p1.y;
		GLfloat nz = (1 - t) * p0.z + t * p1.z;
		ans.push_back({nx, ny, nz});
	}
	return ans;
}

vector<point3d> cube3d(vector<point3d> vertices) {
	vector<point3d> ans;
	for (int i = 0; i < 4; i++) {
		vector<point3d> edge = linear_bezier(vertices[i], vertices[(i + 1) % 4]);
		for (point3d& pt : edge) {
			ans.push_back(pt);
		}
	}
	for (int i = 4; i < 8; i++) {
		vector<point3d> edge = linear_bezier(vertices[i], vertices[4 + ((i + 1) % 4)]);
		for (point3d& pt : edge) {
			ans.push_back(pt);
		}
	}
	for (int i = 0; i < 4; i++) {
		vector<point3d> edge = linear_bezier(vertices[i], vertices[4 + i]);
		for (point3d& pt : edge) {
			ans.push_back(pt);
		}
	}
	return ans;
}

vector<point2d> verticestocube(vector<point2d> vertices) {
	vector<point2d> ans;
	for (int i = 0; i < 4; i++) {
		vector<point2d> edge = line_breshenham(vertices[i].x, vertices[i].y, vertices[(i + 1) % 4].x, vertices[(i + 1) % 4].y);
		for (point2d& pt : edge) {
			ans.push_back(pt);
		}
	}
	for (int i = 4; i < 8; i++) {
		vector<point2d> edge = line_breshenham(vertices[i].x, vertices[i].y, vertices[4 + ((i + 1) % 4)].x, vertices[4 + ((i + 1) % 4)].y);
		for (point2d& pt : edge) {
			ans.push_back(pt);
		}
	}
	for (int i = 0; i < 4; i++) {
		vector<point2d> edge = line_breshenham(vertices[i].x, vertices[i].y, vertices[4+i].x, vertices[4+i].y);
		for (point2d& pt : edge) {
			ans.push_back(pt);
		}
	}
	return ans;
}