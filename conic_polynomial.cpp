#include "utils.h"

vector<pixel> circle_polynomial(GLfloat r) {

	GLfloat x = 0;

	vector<pixel> P;

	while(x<=r) {
		GLfloat y = sqrt(r*r-x*x);
		P.push_back({roundof(x), roundof(y)});
		P.push_back({roundof(-x), roundof(y)});
		P.push_back({roundof(x), roundof(-y)});
		P.push_back({roundof(-x), roundof(-y)});
		P.push_back({roundof(y), roundof(x)});
		P.push_back({roundof(-y), roundof(x)});
		P.push_back({roundof(y), roundof(-x)});
		P.push_back({roundof(-y), roundof(-x)});
		x++;
	}
	
	return P;
}

vector<pixel> ellipse_polynomial(GLfloat a, GLfloat b) {

	GLfloat x = 0, y= b;
	GLfloat m = b / a;

	vector<pixel> P;

	while (b * b * x <= a * a * y) {
		P.push_back({roundof(x), roundof(y)});
		P.push_back({roundof(-x), roundof(y)});
		P.push_back({roundof(x), roundof(-y)});
		P.push_back({roundof(-x), roundof(-y)});
		x++;
		y = m * sqrt(a * a - x * x);
	}

	m = 1 / m;
	while (y >= 0) {
		P.push_back({roundof(x), roundof(y)});
		P.push_back({roundof(-x), roundof(y)});
		P.push_back({roundof(x), roundof(-y)});
		P.push_back({roundof(-x), roundof(-y)});
		y--;
		x = m * sqrt(b * b - y * y);
	}

	return P;
}