#include "utils.h"

vector<point2d> windowtoviewport(GLint xw_min, GLint xw_max, GLint yw_min, GLint yw_max, GLint xv_min, GLint xv_max, GLint yv_min, GLint yv_max, vector<point2d> arr) {
	vector<point2d> ans;
	for (point2d it : arr) {
		if (inside_window(it.x, it.y, xw_min, xw_max, yw_min, yw_max)) {
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
