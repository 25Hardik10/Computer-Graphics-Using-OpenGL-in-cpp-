#include "utils.h"

GLint inside(GLint code) {
	return !code;
}

GLint reject(GLint code1, GLint code2) {
	return code1 & code2;
}

GLint accept(GLint code1, GLint code2) {
	return !(code1 | code2);
}

GLubyte encode(point2d pt, point2d win_min, point2d win_max) {
	GLubyte code= 0;
	if (pt.x < win_min.x) {
		code |= win_left_bit_code;
	}
	if (pt.x > win_max.x) {
		code |= win_right_bit_code;
	}
	if (pt.y < win_min.y) {
		code |= win_down_bit_code;
	}
	if (pt.y > win_max.y) {
		code |= win_up_bit_code;
	}
	return code;
}

vector<point2d> line_clip_Coh_Suth(point2d win_min, point2d win_max, point2d p1, point2d p2) {
	GLint done = false, plotLine = false;
	
	while (!done) {
		GLubyte code1 = encode(p1, win_min, win_max);
		GLubyte code2 = encode(p2, win_min, win_max);
		if (accept(code1, code2)) {
			done = true;
			plotLine = true;
		}
		else if (reject(code1, code2)) {
			done = true;
		}
		else {
			if (inside(code1)) {
				swap(p1,p2);
				swap(code1,code2);
			}
			GLfloat m = 0.0001;
			if (p2.x != p1.x) {
				m = (GLfloat)(p2.y - p1.y) / (GLfloat)(p2.x - p1.x);
			}
			if (code1 & win_left_bit_code) {
				p1.y = p2.y + (win_min.x - p2.x) * m;
				p1.x = win_min.x;
			}
			else if (code1 & win_right_bit_code) {
				p1.y = p2.y + (win_max.x - p2.x) * m;
				p1.x = win_max.x;
			}
			else if (code1 & win_down_bit_code) {
				if (p2.x != p1.x){
					p1.x = p2.x + (GLfloat)(win_min.y - p2.y) / m;
				}
				p1.y = win_min.y;
			}
			else if (code1 & win_up_bit_code) {
				if (p2.x != p1.x) {
					p1.x = p2.x + (GLfloat)(win_max.y - p2.y) / m;
				}
				p1.y = win_max.y;
			}
		}
	}
	if (plotLine) {
		return {p1,p2};
	}
	return {};
}

vector<point2d> normals(vector<point2d> vertices) {
	int n= vertices.size();
	vector<point2d> ans;
	for (int i = 0; i < n; i++) {
		point2d vi= vertices[i];
		point2d vj= vertices[(i+1)%n];
		point2d dir= vj-vi;
		ans.push_back({-dir.y, dir.x});
	}
	return ans;
}

vector<point2d> line_clip_Cyr_Bec(vector<point2d> vertices, point2d p0, point2d p1) {
	int n= vertices.size();
	vector<point2d> nrmls= normals(vertices);
	GLfloat tp= 0, tn= 1;
	for (int i = 0; i < n; i++) {
		point2d pei = vertices[i];
		GLfloat pi = point2d::dot_prod(nrmls[i],p0-pei);
		GLfloat qi = point2d::dot_prod(nrmls[i],p1-p0);
		GLfloat t= (GLfloat)pi/(GLfloat)(-qi);
		if (qi < 0) {
			tn= min(tn, t);
		}
		else {
			tp= max(tp, t);
		}
	}
	point2d a1 = p0 + ((p1 - p0) * tn);
	point2d a2 = p0 + ((p1 - p0) * tp);
	return {a1, a2};
}

vector<point2d> line_clip_Liang_Bar(point2d win_min, point2d win_max, point2d p1, point2d p2) {
	GLfloat dx = p2.x - p1.x;
	GLfloat dy = p2.y - p1.y;

	vector<GLfloat> p(5), q(5);
	p[1] = -dx;
	p[2] = dx;
	p[3] = -dy;
	p[4] = dy;
	q[1] = p1.x - win_min.x;
	q[2] = win_max.x - p1.x;
	q[3] = p1.y - win_min.y;
	q[4] = win_max.y - p1.y;

	GLboolean flag = true;
	for (int k = 1; k <= 4; k++) {
		if (p[k] != 0 || q[k] >= 0) {
			flag = false;
		}
	}
	if (flag) {
		return {};
	}

	GLfloat u1=0,u2=1;

	for (int k = 1; k <= 4; k++) {
		GLfloat rk = q[k]/p[k];
		if (p[k] < 0) {
			u1= max(u1, rk);
		}
		else if(p[k] > 0){
			u2= min(u2, rk);
		}
	}

	if (u1 > u2) {
		return {};
	}
	else if (u1 == 0) {
		GLfloat x2= p1.x + u2*dx;
		GLfloat y2= p1.y + u2*dy;
		return { p1, {x2, y2} };
	}
	else {
		GLfloat x1 = p1.x + u1 * dx;
		GLfloat y1 = p1.y + u1 * dy;
		GLfloat x2 = p1.x + u2 * dx;
		GLfloat y2 = p1.y + u2 * dy;
		return {{x1, y1},{x2, y2}};
	}
	return {};
}

GLint inside(point2d win_min, point2d win_max, int c, point2d pt) {
	switch (c) {
	case 0 :
		if (pt.x < win_min.x) {
			return false;
		}
		break;
	case 1:
		if (pt.x > win_max.x) {
			return false;
		}
		break;
	case 2:
		if (pt.y < win_min.y) {
			return false;
		}
		break;
	case 3:
		if (pt.y > win_max.y) {
			return false;
		}
		break;
	}
	return true;
}

point2d int_point(point2d p1, point2d p2, int c, int val) {
	point2d ans;
	if (c < 2) {
		if (p2.x != p1.x) {
			GLfloat m = (GLfloat)(p2.y - p1.y)/ (GLfloat)(p2.x-p1.x);
			ans.y = p2.y + (val - p2.x) * m;
		}
		ans.x= val;
	}
	else {
		if (p2.y != p1.y) {
			GLfloat minv = (GLfloat)(p2.x - p1.x)/ (GLfloat)(p2.y-p1.y);
			ans.x = p2.x + (val - p2.y) * minv;
		}
		ans.y= val;
	}
	return ans;
}

vector<point2d> line_clip_polygon(point2d win_min, point2d win_max, vector<point2d> vin) {
	vector<GLfloat> clippers = {win_min.x, win_max.x, win_min.y, win_max.y};
	for (int k=0;k<4;k++) {
		vector<point2d> vout;
		int n= vin.size();
		for (int i = 0; i < n; i++) {
			point2d vi= vin[i];
			point2d vj= vin[(i+1)%n];
			GLint checki = inside(win_min, win_max, k, vi);
			GLint checkj = inside(win_min, win_max, k, vj);
			if (checki && !checkj) {
				vout.push_back(int_point(vi, vj, k, clippers[k]));
			}
			else if (checki && checkj) {
				vout.push_back(vj);
			}
			else if (!checki && checkj) {
				vout.push_back(int_point(vi, vj, k, clippers[k]));
				vout.push_back(vj);
			}
		}
		vin= vout;
	}
	return vin;
}