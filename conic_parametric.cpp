#include "utils.h"

vector<pixel> circle_parametric(GLfloat r) {

	vector<pixel> P;
	for (double theta = 0; theta <= PI / 4.0; theta+=0.0001) {
		GLfloat x = r * cos(theta);
		GLfloat y = r * sin(theta);
		P.push_back({roundof(x), roundof(y)});
		P.push_back({roundof(-x), roundof(y)});
		P.push_back({roundof(x), roundof(-y)});
		P.push_back({roundof(-x), roundof(-y)});
		P.push_back({roundof(y), roundof(x)});
		P.push_back({roundof(-y), roundof(x)});
		P.push_back({roundof(y), roundof(-x)});
		P.push_back({roundof(-y), roundof(-x)});
	}
	return P;
}

vector<pixel> ellipse_parametric(GLfloat a, GLfloat b) {

	vector<pixel> P;
	for (double theta = 0; theta <= PI / 2.0; theta+=0.00001) {
		GLfloat x = a * cos(theta);
		GLfloat y = b * sin(theta);
		P.push_back({roundof(x), roundof(y)});
		P.push_back({roundof(-x), roundof(y)});
		P.push_back({roundof(x), roundof(-y)});
		P.push_back({roundof(-x), roundof(-y)});
	}
	return P;
}