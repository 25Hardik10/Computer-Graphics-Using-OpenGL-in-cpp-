#include "utils.h"
#include <iostream>

using namespace std;

vector<vector<vector<GLfloat>>> _3dtohomo(vector<point3d>& arr, GLfloat h) {
	vector<vector<vector<GLfloat>>> ans;
	for (point3d& it : arr) {
		ans.push_back({ {it.x},{it.y}, {it.z}, {h} });
	}
	return ans;
}

vector<point3d> homoto3d(vector<vector<vector<GLfloat>>>& arr) {
	vector<point3d> ans;
	for (vector<vector<GLfloat>>& it : arr) {
		GLfloat x = it[0][0] / it[3][0];
		GLfloat y = it[1][0] / it[3][0];
		GLfloat z = it[2][0] / it[3][0];
		ans.push_back({ x, y, z });
	}
	return ans;
}

vector<vector<GLfloat>> identity3dhomo() {
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ans[i][j] = i == j;
		}
	}
	return ans;
}

vector<vector<GLfloat>> translate3dhomo(GLfloat tx, GLfloat ty, GLfloat tz) {
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ans[i][j] = i == j;
		}
	}
	ans[0][3] = tx;
	ans[1][3] = ty;
	ans[2][3] = tz;
	return ans;
}

vector<vector<GLfloat>> scale3dhomo(GLfloat sx, GLfloat sy, GLfloat sz) {
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	ans[0][0] = sx;
	ans[1][1] = sy;
	ans[2][2] = sz;
	ans[3][3] = 1;
	return ans;
}

vector<vector<GLfloat>> rotate3dzhomo(double theta) {
	theta = theta * PI / 180.0;
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	ans[0][0] = cos(theta);
	ans[0][1] = -sin(theta);
	ans[1][0] = sin(theta);
	ans[1][1] = cos(theta);
	ans[2][2] = 1;
	ans[3][3] = 1;
	return ans;
}

vector<vector<GLfloat>> rotate3dxhomo(double theta) {
	theta = theta * PI / 180.0;
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	ans[0][0] = 1;
	ans[1][1] = cos(theta);
	ans[1][2] = -sin(theta);
	ans[2][1] = sin(theta);
	ans[2][2] = cos(theta);
	ans[3][3] = 1;
	return ans;
}

vector<vector<GLfloat>> rotate3dyhomo(double theta) {
	theta = theta * PI / 180.0;
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	ans[0][0] = cos(theta);
	ans[0][2] = sin(theta);
	ans[1][1] = 1;
	ans[2][0] = -sin(theta);
	ans[2][2] = cos(theta);
	ans[3][3] = 1;
	return ans;
}

vector<vector<GLfloat>> reflectxy3dhomo() {
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	ans[0][0] = 1;
	ans[1][1] = 1;
	ans[2][2] = -1;
	ans[3][3] = 1;
	return ans;
}

vector<vector<GLfloat>> reflectyz3dhomo() {
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	ans[0][0] = -1;
	ans[1][1] = 1;
	ans[2][2] = 1;
	ans[3][3] = 1;
	return ans;
}

vector<vector<GLfloat>> reflectxz3dhomo() {
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	ans[0][0] = 1;
	ans[1][1] = -1;
	ans[2][2] = 1;
	ans[3][3] = 1;
	return ans;
}

vector<vector<GLfloat>> shear3dhomo(GLfloat shxy, GLfloat shxz, GLfloat shyx, GLfloat shyz, GLfloat shzx, GLfloat shzy) {
	vector<vector<GLfloat>> ans(4, vector<GLfloat>(4, 0));
	ans[0][0] = 1;
	ans[0][1] = shxy;
	ans[0][2] = shxz;
	ans[1][0] = shyx;
	ans[1][1] = 1;
	ans[1][2] = shyz;
	ans[2][0] = shzx;
	ans[2][1] = shzy;
	ans[2][2] = 1;
	ans[3][3] = 1;
	return ans;
}