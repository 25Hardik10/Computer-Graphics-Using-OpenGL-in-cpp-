#include "utils.h"

vector<pixel> circle_midpoint(GLfloat r) {

	GLint x = 0, y = r;
	GLfloat p = 1.25 - r;

	vector<pixel> P;
	while (x<y) {
		if (p < 0.0) {
			p += 3.0 + 2.0 * x;
		}
		else {
			p += 5.0 + 2.0 * x - 2.0 * y;
			y -= 1;
		}
		x += 1.0;
		P.push_back({ y, x});
		P.push_back({ x, y});
		P.push_back({-x, y});
		P.push_back({-y, x});
		P.push_back({-y, -x});
		P.push_back({-x, -y});
		P.push_back({ x, -y});
		P.push_back({ y, -x});
	}
	return P;
}

vector<pixel> ellipse_midpoint(GLfloat a, GLfloat b) {

	GLint x = 0, y = b;
	GLfloat p1 = 0.25*a*a + b*b - a*a*b;
	
	vector<pixel> P;
	while (b*b*x <= a*a*y) {
		P.push_back({x, y});
		P.push_back({- x, y});
		P.push_back({- x, - y});
		P.push_back({x, - y});
		x += 1;
		if (p1 < 0) {
			p1 += 2*b*b*x + b*b;
		}
		else {
			y -= 1;
			p1 += 2*b*b*x + b*b - 2*a*a*y;
		}
		
	}

	GLfloat p2 = b*b*(x + 0.5)*(x + 0.5) + a*a*(y - 1)*(y - 1) - a*a*b*b;
	while (y > 0) {
		P.push_back({ x, y});
		P.push_back({ -x, y});
		P.push_back({ -x, -y});
		P.push_back({ x, -y});
		y -= 1;
		if (p2 > 0) {
			p2 += -2*a*a*y + a*a;
		}
		else {
			x += 1;
			p2 += -2*a*a*y + 2*b*b*x + a*a;
		}
	}
	return P;
}