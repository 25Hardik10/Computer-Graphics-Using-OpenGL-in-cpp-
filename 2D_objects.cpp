#include "utils.h"

vector<pixel> polygon(vector<point2d> vertices) {
	vector<pixel> ans;
	int n= vertices.size();
	for (int i = 0; i < n; i++) {
		vector<pixel> edge = line_breshenham(vertices[i], vertices[(i + 1) % n]);
		for (pixel& it : edge) {
			ans.push_back(it);
		}
	}
	return ans;
}
