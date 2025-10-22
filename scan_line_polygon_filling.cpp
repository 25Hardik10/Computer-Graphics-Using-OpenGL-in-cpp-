#include "utils.h"
#include <climits>
#include <algorithm>
using namespace std;

struct edge {
	GLint y_min;
	GLint y_max;
	GLint x_y_min;
	GLint dx;
	GLint dy;
	GLint dc;
	GLint dir;
};

vector<pixel> scan_line_polygon_filling(vector<pixel>& vertices) {

	int v = vertices.size();

	GLint Y_min= INT_MAX,Y_max=INT_MIN;
	vector<edge> edge_table;
	{
		int a= v-2;
		int b= v-1;
		for (int i = 0; i < v; i++) {
			if (vertices[b].y == vertices[i].y) {
				// horizontal edge
			}
			else if (vertices[a].y <= vertices[b].y && vertices[b].y <= vertices[i].y) {
				GLint dx = vertices[i].x-vertices[b].x;
				GLint dy = vertices[i].y-vertices[b].y;
				GLint dir = dx >=0 ? 1 : -1;
				dx = abs(dx);
				GLint x_y_min = dir > 0 ? vertices[b].x + dx / dy : vertices[b].x - dx / dy;
				edge_table.push_back({vertices[b].y+1,vertices[i].y,x_y_min, dx, dy, dx%dy, dir});
				Y_min = min(Y_min, vertices[b].y+1);
				Y_max = max(Y_max, vertices[i].y);
			}
			else if (vertices[a].y >= vertices[b].y && vertices[b].y >= vertices[i].y) {
				GLint dx = vertices[b].x-vertices[i].x;
				GLint dy = vertices[b].y-vertices[i].y;
				GLint dir = dx >= 0 ? 1 : -1;
				dx = abs(dx);
				edge_table.push_back({vertices[i].y,vertices[b].y-1,vertices[i].x, dx, dy, 0, dir});
				Y_min = min(Y_min, vertices[i].y);
				Y_max = max(Y_max, vertices[b].y-1);
			}
			else {
				int mini= i;
				int maxi= b;
				if (vertices[b].y < vertices[i].y) {
					mini= b;
					maxi= i;
				}
				GLint dx = vertices[maxi].x-vertices[mini].x;
				GLint dy = vertices[maxi].y-vertices[mini].y;
				GLint dir = dx >= 0 ? 1 : -1;
				dx = abs(dx);
				edge_table.push_back({ vertices[mini].y,vertices[maxi].y,vertices[mini].x, dx, dy, 0, dir});
				Y_min = min(Y_min, vertices[mini].y);
				Y_max = max(Y_max, vertices[maxi].y);
			}
			a=b;
			b=i;
		}
	}
	sort(edge_table.begin(), edge_table.end(), [](const edge& a, const edge& b) {
		if (a.y_min != b.y_min) {
			return a.y_min < b.y_min;
		}
		return a.x_y_min < b.x_y_min;
	});
	int e= edge_table.size();
	
	vector<vector<edge>> sorted_edge_table(Y_max-Y_min+1);
	for (int i = 0; i < e; i++) {
		sorted_edge_table[-Y_min+edge_table[i].y_min].push_back(edge_table[i]);
	}

	vector<pixel> P;

	vector<edge> active_table;
	for (int y = Y_min; y <= Y_max; y++) {
		for (int i = 0; i < (int)sorted_edge_table[-Y_min + y].size(); i++) {
			active_table.push_back(sorted_edge_table[-Y_min+y][i]);
		}
		sort(active_table.begin(), active_table.end(), [](const edge& a, const edge& b) {
			return a.x_y_min<b.x_y_min;
		});
		int o=0;
		for (int e = 1; e < (int)active_table.size(); e+=2) {
			for (GLint x = active_table[o].x_y_min; x <= active_table[e].x_y_min; x++) {
				P.push_back({x,y});
			}
			o=e+1;
		}
		for (int i = 0; i < (int)active_table.size(); i++) {
			if (active_table[i].y_max == y) {
				active_table.erase(active_table.begin()+i);
				i--;
				continue;
			}
			active_table[i].dc+=active_table[i].dx;
			while (active_table[i].dc >= active_table[i].dy) {
				active_table[i].dc -= active_table[i].dy;
				active_table[i].x_y_min = active_table[i].x_y_min + active_table[i].dir;
			}
		}
	}
	return P;
}