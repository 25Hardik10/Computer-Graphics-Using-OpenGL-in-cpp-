#include "utils.h"

bool inside_window(point2d p, point2d w_min, point2d w_max) {
	if (p.x <= w_max.x && p.x >= w_min.x && p.y <= w_max.y && p.y >= w_min.y) {
		return true;
	}
	return false;
}

vector<point2d> windowtoviewport(point2d w_min, point2d w_max, point2d v_min, point2d v_max, vector<point2d> arr) {
	GLfloat xw_min= w_min.x, yw_min=w_min.y, xw_max=w_max.x,yw_max=w_max.y, xv_min = v_min.x, yv_min = v_min.y, xv_max = v_max.x, yv_max = v_max.y;
	
	vector<point2d> ans;
	for (point2d it : arr) {
		if (inside_window(it, w_min, w_max)) {
			ans.push_back(it);
		}
	}

	GLfloat sx = (GLfloat)(xv_max - xv_min)/(xw_max - xw_min);
	GLfloat sy = (GLfloat)(yv_max - yv_min)/(yw_max - yw_min);

	vector<vector<GLfloat>> matrix = identity2dhomo();
	matrix = matrixmultiplication(translate2dhomo(-xw_min, -yw_min), matrix);
	matrix = matrixmultiplication(scale2dhomo(sx, sy), matrix);
	matrix = matrixmultiplication(translate2dhomo(xv_min, yv_min), matrix);

	vector<vector<vector<GLfloat>>> homo = _2dtohomo(ans);
	for (vector<vector<GLfloat>>& it : homo) {
		it = matrixmultiplication(matrix, it);
	}
	ans = homoto2d(homo);

	return ans;
}
