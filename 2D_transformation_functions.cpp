#include "utils.h"

vector<point2d> translate2d(GLfloat tx, GLfloat ty, vector<point2d> arr) {
	vector<point2d> ans;
	for (point2d& it : arr) {
		GLint nx= it.x + tx;
		GLint ny= it.y + ty;
		ans.push_back({nx, ny});
	}
	return ans;
}

vector<point2d> scale2d(GLfloat sx, GLfloat sy, vector<point2d> arr) {
	vector<point2d> ans;
	for (point2d& it : arr) {
		GLint nx = it.x * sx;
		GLint ny = it.y * sy;
		ans.push_back({ nx, ny });
	}
	return ans;
}

vector<point2d> rotate2d(double theta, vector<point2d> arr) {
	theta = theta*PI/180.0;
	vector<point2d> ans;
	for (point2d& it : arr) {
		GLint nx = it.x * cos(theta) - it.y * sin(theta);
		GLint ny = it.x * sin(theta) + it.y * cos(theta);
		ans.push_back({ nx, ny });
	}
	return ans;
}

vector<point2d> reflectx2d(vector<point2d> arr) {
	vector<point2d> ans;
	for (point2d& it : arr) {
		GLint nx = it.x;
		GLint ny = -it.y;
		ans.push_back({ nx, ny });
	}
	return ans;
}

vector<point2d> reflecty2d(vector<point2d> arr) {
	vector<point2d> ans;
	for (point2d& it : arr) {
		GLint nx = -it.x;
		GLint ny = it.y;
		ans.push_back({ nx, ny });
	}
	return ans;
}

vector<point2d> shear2d(GLfloat shx, GLfloat shy, vector<point2d> arr) {
	vector<point2d> ans;
	for (point2d& it : arr) {
		GLint nx = it.x + shx * it.y;
		GLint ny = it.y + shy * it.x;
		ans.push_back({ nx, ny });
	}
	return ans;
}