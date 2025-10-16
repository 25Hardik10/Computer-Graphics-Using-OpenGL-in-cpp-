#include "utils.h"

vector<point2d> circle_breshenham(GLint r) {

	GLint x = 0, y = r;
	GLint d = 2 * r - 3;
	
	vector<point2d> P;
	while (x < y) {
		P.push_back({ x,  y});
		P.push_back({- x,  y});
		P.push_back({ y,  x});
		P.push_back({- y,  x});
		P.push_back({ x, - y});
		P.push_back({- x, - y});
		P.push_back({ y, - x});
		P.push_back({- y, - x});
		
		x += 1;
		if (d > 0) {
			d += -4 * x - 2;
		}
		else {
			y -= 1;
			d += -4 * x + 4 * y - 2;
		}
	}
	return P;
}

vector<point2d> ellipse_breshenham(GLint a, GLint b) {

	GLint x = 0, y = b;
	GLint d = 2 * a * a * b - 2 * b * b - a * a;

	vector<point2d> P;
	while (b * b * x < a * a * y) {
		P.push_back({ x,  y});
		P.push_back({- x,  y});
		P.push_back({ x, - y});
		P.push_back({- x, - y});

		x += 1;
		if (d > 0) {
			d += -4 * b * b * x - 2 * b * b;
		}
		else {
			y -= 1;
			d += -4 * b * b * x - 2 * b * b + 4 * a * a * y;
		}
	}

	d = 2 * b * b * (x * x + x + 1) + 2 * a * a * (y - 1) * (y - 1) - 2 * a * a * b * b - b * b;
	while (y >= 0) {
		P.push_back({ x,  y});
		P.push_back({- x,  y});
		P.push_back({ x, - y});
		P.push_back({- x, - y});

		y -= 1;
		if (d > 0) {
			d += -4 * a * a * y + 2 * a * a;
		}
		else {
			x += 1;
			d += -4 * a * a * y + 2 * a * a + 4 * b * b * x;
		}
	}

	return P;
}