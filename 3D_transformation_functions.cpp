#include "utils.h"

vector<point3d> translate3d(GLfloat tx, GLfloat ty, GLfloat tz, vector<point3d>& arr) {
	vector<point3d> ans;
	for (point3d& it : arr) {
		GLfloat nx = it.x + tx;
		GLfloat ny = it.y + ty;
		GLfloat nz = it.z + tz;
		ans.push_back({ nx, ny, nz });
	}
	return ans;
}

vector<point3d> scale3d(GLfloat sx, GLfloat sy, GLfloat sz, vector<point3d>& arr) {
	vector<point3d> ans;
	for (point3d& it : arr) {
		GLfloat nx = it.x * sx;
		GLfloat ny = it.y * sy;
		GLfloat nz = it.z * sz;
		ans.push_back({ nx, ny, nz });
	}
	return ans;
}

vector<point3d> rotate3dz(double theta, vector<point3d>& arr) {
	theta = theta * PI / 180.0;
	vector<point3d> ans;
	for (point3d& it : arr) {
		GLfloat nx = it.x * cos(theta) - it.y * sin(theta);
		GLfloat ny = it.x * sin(theta) + it.y * cos(theta);
		GLfloat nz = it.z;
		ans.push_back({ nx, ny, nz });
	}
	return ans;
}

vector<point3d> rotate3dx(double theta, vector<point3d>& arr) {
	theta = theta * PI / 180.0;
	vector<point3d> ans;
	for (point3d& it : arr) {
		GLfloat nx = it.x;
		GLfloat ny = it.y * cos(theta) - it.z * sin(theta);
		GLfloat nz = it.y * sin(theta) + it.z * cos(theta);
		ans.push_back({ nx, ny, nz });
	}
	return ans;
}

vector<point3d> rotate3dy(double theta, vector<point3d>& arr) {
	theta = theta * PI / 180.0;
	vector<point3d> ans;
	for (point3d& it : arr) {
		GLfloat nx = it.x * cos(theta) + it.z * sin(theta);
		GLfloat ny = it.y;
		GLfloat nz = -it.x * sin(theta) + it.z * cos(theta);
		ans.push_back({ nx, ny, nz });
	}
	return ans;
}

vector<point3d> reflect3dxy(vector<point3d>& arr) {
	vector<point3d> ans;
	for (point3d& it : arr) {
		GLfloat nx = it.x;
		GLfloat ny = it.y;
		GLfloat nz = it.z;
		ans.push_back({ nx, ny, nz });
	}
	return ans;
}

vector<point3d> reflect3dyz(vector<point3d>& arr) {
	vector<point3d> ans;
	for (point3d& it : arr) {
		GLfloat nx = -it.x;
		GLfloat ny = it.y;
		GLfloat nz = it.z;
		ans.push_back({ nx, ny, nz });
	}
	return ans;
}

vector<point3d> reflect3dxz(vector<point3d>& arr) {
	vector<point3d> ans;
	for (point3d& it : arr) {
		GLfloat nx = it.x;
		GLfloat ny = -it.y;
		GLfloat nz = it.z;
		ans.push_back({ nx, ny, nz });
	}
	return ans;
}

vector<point3d> shear3d(GLfloat shxy, GLfloat shxz, GLfloat shyx, GLfloat shyz, GLfloat shzx, GLfloat shzy, vector<point3d>& arr) {
	vector<point3d> ans;
	for (point3d& it : arr) {
		GLfloat nx = it.x + shxy * it.y + shxz * it.z;
		GLfloat ny = it.y + shyx * it.x + shyz * it.z;
		GLfloat nz = it.z + shzx * it.x + shzy * it.y;
		ans.push_back({ nx, ny, nz });
	}
	return ans;
}