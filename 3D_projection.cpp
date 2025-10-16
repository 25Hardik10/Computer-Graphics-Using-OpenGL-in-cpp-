#include "utils.h"

vector<vector<GLfloat>> Mw2v(point3d camera, point3d pup, point3d coi) {
	point3d nv = camera - coi;
	point3d vv = pup - camera;
	point3d n = nv / mod(nv);
	point3d v = vv / mod(vv);
	point3d u = cross_prod(v, n);

	vector<vector<GLfloat>> R = { 
								{u.x,u.y,u.z,0},
								{v.x,v.y,v.z,0},
								{n.x,n.y,n.z,0},
								{0,0,0,1} };

	vector<vector<GLfloat>> T = translate3dhomo(-camera.x, -camera.y, -camera.z);
	return matrixmultiplication(R, T);
}

vector<vector<vector<GLfloat>>> camera_transform(point3d camera, point3d pup, point3d coi, vector<vector<vector<GLfloat>>> points_homo) {
	vector<vector<GLfloat>> mw2v = Mw2v(camera, pup, coi);
	vector<vector<vector<GLfloat>>> ans;
	for (vector<vector<GLfloat>>& it : points_homo) {
		ans.push_back(matrixmultiplication(mw2v, it));
	}
	return ans;
}

vector<vector<GLfloat>> Tpsp(GLfloat d) {
	GLfloat dinv = 1.0 / d;
	return { {1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{0,0,dinv,0} };
}

vector<vector<vector<GLfloat>>> perspective_projection(GLfloat d, vector<vector<vector<GLfloat>>> points_homo) {
	vector<vector<GLfloat>> tpsp = Tpsp(d);
	vector<vector<vector<GLfloat>>> ans;
	for (vector<vector<GLfloat>>& it : points_homo) {
		ans.push_back(matrixmultiplication(tpsp, it));
	}
	return ans;
}

vector<vector<GLfloat>> Tpar(GLfloat d) {
	return { {1,0,0,0},
			{0,1,0,0},
			{0,0,0,-d},
			{0,0,0,1} };
}

vector<vector<vector<GLfloat>>> parallel_projection(GLfloat d, vector<vector<vector<GLfloat>>> points_homo) {
	vector<vector<GLfloat>> tpar = Tpar(d);
	vector<vector<vector<GLfloat>>> ans;
	for (vector<vector<GLfloat>>& it : points_homo) {
		ans.push_back(matrixmultiplication(tpar, it));
	}
	return ans;
}