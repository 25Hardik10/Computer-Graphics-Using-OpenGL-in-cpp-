#ifndef UTILS_H
#define UTILS_H
#define PI 3.14159265358979323846

#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

void swap(GLint& a, GLint& b);
void swap(GLfloat& a, GLfloat& b);
void swap(GLubyte& a, GLubyte& b);

GLint roundof(GLfloat n);

struct point2d {
	GLint x;
	GLint y;

	void swap(point2d& p1, point2d& p2) {
		point2d temp = p1;
		p1 = p2;
		p2 = temp;
	}

	static GLfloat dot(point2d& p1, point2d p2) {
		return p1.x * p2.x + p1.y * p2.y;
	}

	point2d operator-(const point2d& pt) {
		GLint nx= this->x - pt.x;
		GLint ny= this->y - pt.y;
		return {nx,ny};
	}

	point2d operator+(const point2d& pt) {
		GLint nx = this->x + pt.x;
		GLint ny = this->y + pt.y;
		return { nx,ny };
	}

	point2d operator*(const GLfloat& scalar) {
		GLint nx= this->x*scalar;
		GLint ny= this->y*scalar;
		return {nx,ny};
	}
};

struct point3d {
	GLfloat x;
	GLfloat y;
	GLfloat z;

	point3d operator/(const GLfloat& deno) {
		GLfloat nx = this->x / deno;
		GLfloat ny = this->y / deno;
		GLfloat nz = this->z / deno;
		return { nx,ny,nz };
	}

	point3d operator-(const point3d& pt) {
		GLfloat nx= this->x - pt.x;
		GLfloat ny= this->y - pt.y;
		GLfloat nz= this->z - pt.z;
		return { nx,ny,nz };
	}

	point3d operator+(const point3d& pt) {
		GLfloat nx = this->x + pt.x;
		GLfloat ny = this->y + pt.y;
		GLfloat nz = this->z + pt.z;
		return { nx,ny,nz };
	}
};

void plot2d(vector<point2d> arr);

vector<point2d> line_polynomial(GLfloat m, GLfloat c);
vector<point2d> line_dda(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
vector<point2d> line_breshenham(GLint x1, GLint y1, GLint x2, GLint y2);
vector<point2d> line_dashed_breshenham(GLint x1, GLint y1, GLint x2, GLint y2, GLint dl, GLint idl);

vector<point2d> circle_polynomial(GLfloat r);
vector<point2d> circle_parametric(GLfloat r);
vector<point2d> circle_midpoint(GLfloat r); 
vector<point2d> circle_breshenham(GLint r);

vector<point2d> ellipse_polynomial(GLfloat a, GLfloat b);
vector<point2d> ellipse_parametric(GLfloat a, GLfloat b);
vector<point2d> ellipse_midpoint(GLfloat a, GLfloat b);
vector<point2d> ellipse_breshenham(GLint a, GLint b);

vector<point2d> scan_line_polygon_filling(vector<point2d> vertices);
void seed_fill();

vector<point2d> verticestopoints2d(vector<vector<GLint>> vertices);

vector<point2d> translate2d(GLfloat tx, GLfloat ty, vector<point2d> arr);
vector<point2d> scale2d(GLfloat sx, GLfloat sy, vector<point2d> arr);
vector<point2d> rotate2d(double theta, vector<point2d> arr);
vector<point2d> reflectx2d(vector<point2d> arr);
vector<point2d> reflecty2d(vector<point2d> arr);
vector<point2d> shear2d(GLfloat shx, GLfloat shy, vector<point2d> arr);

vector<vector<vector<GLfloat>>> _2dtohomo(vector<point2d> arr, GLfloat h = 1);
vector<point2d> homoto2d(vector<vector<vector<GLfloat>>> arr);
vector<vector<GLfloat>> matrixmultiplication(vector<vector<GLfloat>> m1, vector<vector<GLfloat>> m2);
vector<vector<GLfloat>> identity2dhomo();
vector<vector<GLfloat>> translate2dhomo(GLfloat tx, GLfloat ty);
vector<vector<GLfloat>> scale2dhomo(GLfloat sx, GLfloat sy);
vector<vector<GLfloat>> rotate2dhomo(double theta);
vector<vector<GLfloat>> reflectx2dhomo();
vector<vector<GLfloat>> reflecty2dhomo();
vector<vector<GLfloat>> shear2dhomo(GLfloat shx, GLfloat shy);

bool inside_window(GLint x, GLint y, GLint x_min, GLint x_max, GLint y_min, GLint y_max);
vector<point2d> windowtoviewport(GLint xw_min, GLint xw_max, GLint yw_min, GLint yw_max, GLint xv_min, GLint xv_max, GLint yv_min, GLint yv_max, vector<point2d> arr);

vector<point3d> translate3d(GLfloat tx, GLfloat ty, GLfloat tz, vector<point3d> arr);
vector<point3d> scale3d(GLfloat sx, GLfloat sy, GLfloat sz, vector<point3d> arr);
vector<point3d> rotate3dz(double theta, vector<point3d> arr);
vector<point3d> rotate3dx(double theta, vector<point3d> arr);
vector<point3d> rotate3dy(double theta, vector<point3d> arr);
vector<point3d> reflect3dxy(vector<point3d> arr);
vector<point3d> reflect3dyz(vector<point3d> arr);
vector<point3d> reflect3dxz(vector<point3d> arr);
vector<point3d> shear3d(GLfloat shxy, GLfloat shxz, GLfloat shyx, GLfloat shyz, GLfloat shzx, GLfloat shzy, vector<point3d> arr);

vector<vector<vector<GLfloat>>> _3dtohomo(vector<point3d> arr, GLfloat h);
vector<point3d> homoto3d(vector<vector<vector<GLfloat>>> arr);
vector<vector<GLfloat>> identity3dhomo();
vector<vector<GLfloat>> translate3dhomo(GLfloat tx, GLfloat ty, GLfloat tz);
vector<vector<GLfloat>> scale3dhomo(GLfloat sx, GLfloat sy, GLfloat sz);
vector<vector<GLfloat>> rotate3dzhomo(double theta);
vector<vector<GLfloat>> rotate3dxhomo(double theta);
vector<vector<GLfloat>> rotate3dyhomo(double theta);
vector<vector<GLfloat>> reflectxy3dhomo();
vector<vector<GLfloat>> reflectyz3dhomo();
vector<vector<GLfloat>> reflectxz3dhomo();
vector<vector<GLfloat>> shear3dhomo(GLfloat shxy, GLfloat shxz, GLfloat shyx, GLfloat shyz, GLfloat shzx, GLfloat shzy);

vector<point3d> linear_bezier(point3d p0, point3d p1);
vector<point3d> cube3d(vector<point3d> vertices);
vector<point2d> verticestocube(vector<point2d> vertices);

GLfloat mod(point3d pt);
point3d cross_prod(point3d a, point3d b);

vector<vector<GLfloat>> Mw2v(point3d camera, point3d pup, point3d coi);
vector<vector<vector<GLfloat>>> camera_transform(point3d camera, point3d pup, point3d coi, vector<vector<vector<GLfloat>>> points_homo);
vector<vector<GLfloat>> Tpsp(GLfloat d);
vector<vector<vector<GLfloat>>> perspective_projection(GLfloat d, vector<vector<vector<GLfloat>>> points_homo);
vector<vector<GLfloat>> Tpar(GLfloat d);
vector<vector<vector<GLfloat>>> parallel_projection(GLfloat d, vector<vector<vector<GLfloat>>> points_homo);

GLint inside(GLint code);
GLint reject(GLint code1, GLint code2);
GLint accept(GLint code1, GLint code2);
const GLubyte win_left_bit_code = 1;
const GLubyte win_right_bit_code = 2;
const GLubyte win_down_bit_code = 4;
const GLubyte win_up_bit_code = 8;
GLubyte encode(point2d pt, point2d win_min, point2d win_max);
void line_clip_Coh_Suth(point2d win_min, point2d win_max, point2d p1, point2d p2);
vector<point2d> normals(vector<point2d> vertices);
void line_clip_Cyr_Bec(vector<point2d> vertices, point2d p1, point2d p2);
void line_clip_Liang_Bar(point2d win_min, point2d win_max, point2d p1, point2d p2);
GLint inside(point2d win_min, point2d win_max, int c, point2d pt);
point2d int_point(point2d p1, point2d p2, int c, int val);
void line_clip_polygon(point2d win_min, point2d win_max, vector<point2d> plygn);

vector<point2d> polygon(vector<point2d> vertices);

//samples

void rotating_cube();

#endif
