#include "utils.h"
#include <iostream>

using namespace std;

vector<vector<vector<GLfloat>>> _2dtohomo(vector<point2d> arr, GLfloat h) {
	vector<vector<vector<GLfloat>>> ans;
	for (point2d& it : arr) {
		ans.push_back({{(GLfloat)it.x},{(GLfloat)it.y},{h}});
	}
	return ans;
}

vector<point2d> homoto2d(vector<vector<vector<GLfloat>>> arr) {
	vector<point2d> ans;
	for (vector<vector<GLfloat>>& it : arr) {
		GLfloat x= it[0][0] / it[2][0];
		GLfloat y= it[1][0] / it[2][0];
		ans.push_back({x,y});
	}
	return ans;
}

vector<vector<GLfloat>> matrixmultiplication(vector<vector<GLfloat>> m1, vector<vector<GLfloat>> m2) {
	int p= m1.size(), q= m1[0].size(), r= m2.size(), s= m2[0].size();
	if (q != r) {
		cerr<<"Invalid Matrix Multiplication"<<endl;
		return {};
	}
	vector<vector<GLfloat>> ans(p, vector<GLfloat>(s,0));
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < s; j++) {
			for (int k = 0; k < q; k++) {
				ans[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
	return ans;
}

vector<vector<GLfloat>> identity2dhomo() {
	vector<vector<GLfloat>> ans(3, vector<GLfloat>(3, 0));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ans[i][j]= i==j;
		}
	}
	return ans;
}

vector<vector<GLfloat>> translate2dhomo(GLfloat tx, GLfloat ty) {
	vector<vector<GLfloat>> ans(3, vector<GLfloat>(3, 0));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ans[i][j] = i == j;
		}
	}
	ans[0][2]= tx;
	ans[1][2]= ty;
	return ans;
}

vector<vector<GLfloat>> scale2dhomo(GLfloat sx, GLfloat sy) {
	vector<vector<GLfloat>> ans(3, vector<GLfloat>(3, 0));
	ans[0][0] = sx;
	ans[1][1] = sy;
	ans[2][2] = 1;
	return ans;
}

vector<vector<GLfloat>> rotate2dhomo(double theta) {
	theta = theta * PI / 180.0;
	vector<vector<GLfloat>> ans(3, vector<GLfloat>(3,0));
	ans[0][0] = cos(theta);
	ans[0][1] = -sin(theta);
	ans[1][0] = sin(theta);
	ans[1][1] = cos(theta);
	ans[2][2] = 1;
	return ans;
}

vector<vector<GLfloat>> reflectx2dhomo() {
	vector<vector<GLfloat>> ans(3, vector<GLfloat>(3, 0));
	ans[0][0] = 1;
	ans[1][1] = -1;
	ans[2][2] = 1;
	return ans;
}

vector<vector<GLfloat>> reflecty2dhomo() {
	vector<vector<GLfloat>> ans(3, vector<GLfloat>(3, 0));
	ans[0][0] = -1;
	ans[1][1] = 1;
	ans[2][2] = 1;
	return ans;
}

vector<vector<GLfloat>> shear2dhomo(GLfloat shx, GLfloat shy) {
	vector<vector<GLfloat>> ans(3, vector<GLfloat>(3, 0));
	ans[0][0] = 1;
	ans[0][1] = shx;
	ans[1][0] = shy;
	ans[1][1] = 1;
	ans[2][2] = 1;
	return ans;
}