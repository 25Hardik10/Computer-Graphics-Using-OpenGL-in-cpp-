#include "utils.h"

vector<point2d> polygon(vector<point2d> vertices) {
	vector<point2d> ans;
	int n= vertices.size();
	for (int i = 0; i < n; i++) {
		vector<point2d> edge = line_breshenham(vertices[i].x, vertices[i].y, vertices[(i + 1) % n].x, vertices[(i + 1) % n].y);
		for (point2d& it : edge) {
			ans.push_back(it);
		}
	}
	return ans;
}
