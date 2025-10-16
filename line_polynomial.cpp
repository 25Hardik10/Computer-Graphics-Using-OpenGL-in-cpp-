#include "utils.h"

vector<point2d> line_polynomial(GLfloat m, GLfloat c) {
	vector<point2d> ans;
	for (GLfloat x = -1000; x <= 1000; x+=1) {
		GLfloat y= m*x + c;
		ans.push_back({roundof(x),roundof(y)});
	}
	return ans;
}