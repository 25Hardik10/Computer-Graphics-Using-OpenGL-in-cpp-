#include "utils.h"

vector<pixel> line_polynomial(GLfloat m, GLfloat c) {
	vector<pixel> ans;
	for (GLfloat x = -1000; x <= 1000; x+=1) {
		GLfloat y= m*x + c;
		ans.push_back({roundof(x),roundof(y)});
	}
	return ans;
}