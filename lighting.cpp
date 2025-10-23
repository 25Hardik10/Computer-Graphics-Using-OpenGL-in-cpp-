#include "utils.h"

void lighting(point3d source, vector<point3d> normals, point3d eye, vector<point3d>& pts, GLfloat Ia, GLfloat Il, GLfloat ka, GLfloat kd, GLfloat ks, GLfloat n, GLfloat a0, GLfloat a1, GLfloat a2, GLfloat a) {
	GLfloat Ii= ka* Ia + kd * Il + ks * Il;
	int m= pts.size();
	GLfloat temp = 0;
	for (int i=0;i<m;i++) {
		GLfloat d= point3d::mod(pts[i]-source);
		GLfloat af =1/(a0+a1*d+a2*d*d);
		point3d lv = source - pts[i];
		point3d l = lv / point3d::mod(lv);
		point3d nrml = normals[i] / point3d::mod(normals[i]);
		GLfloat cos_theta = point3d::dot_prod(nrml, l);
		point3d r = nrml * 2 * cos_theta - l;
		point3d ev = eye - pts[i];
		point3d e = ev / point3d::mod(ev);
		GLfloat cos_phi = point3d::dot_prod(r, e);
		GLfloat Iambi = ka * Ia;
		GLfloat Idiff = kd * Il * max(cos_theta, (GLfloat)0);
		GLfloat Ispec = ks * Il * max(pow(cos_phi, n), (float)0);
		GLfloat I = Iambi + af*(Idiff + Ispec);
		GLfloat I_norm = I/Ii;
		pts[i].r = pts[i].g = pts[i].b = I_norm;
	}
}