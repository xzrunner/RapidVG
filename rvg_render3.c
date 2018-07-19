#include "rvg_render.h"
#include "rvg_math.h"

#include <c_wrap_sl.h>

#define TYPE_POINTS			0x0000
#define TYPE_LINES			0x0001
#define TYPE_LINE_LOOP		0x0002
#define TYPE_LINE_STRIP		0x0003
#define TYPE_TRIANGLES		0x0004
#define TYPE_TRIANGLE_STRIP	0x0005
#define TYPE_TRIANGLE_FAN	0x0006
#define TYPE_QUADS			0x0007
// #define TYPE_QUAD_STRIP	0x0008
// #define TYPE_POLYGON		0x0009

void
rvg_point3(float x, float y, float z) {
	sl_shape3_type(TYPE_POINTS);

	float coords[3];
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
	sl_shape3_draw(coords, 1);
}

void
rvg_line3(float x0, float y0, float z0, float x1, float y1, float z1) {
	sl_shape3_type(TYPE_LINES);

	float coords[6];
	coords[0] = x0;
	coords[1] = y0;
	coords[2] = z0;
	coords[3] = x1;
	coords[4] = y1;
	coords[5] = z1;
	sl_shape3_draw(coords, 2);
}

void
rvg_lines3(const float* positions, int count) {
	sl_shape3_type(TYPE_LINES);
	sl_shape3_draw(positions, count);
}

void
rvg_polyline3(const float* positions, int count, bool loop) {
	if (count < 2) {
		return;
	}

	sl_shape3_type(TYPE_LINE_STRIP);
	sl_shape3_draw_node(positions[0], positions[1], positions[2], true);
	sl_shape3_draw(positions, count);
	if (loop) {
		sl_shape3_draw_node(positions[0], positions[1], positions[2], false);
		sl_shape3_draw_node(positions[0], positions[1], positions[2], true);
	} else {
		sl_shape3_draw_node(positions[(count - 1) * 3], positions[(count - 1) * 3 + 1], positions[(count - 1) * 3 + 2], true);
	}
}

void
rvg_triangles3(const float* positions, int count) {
	sl_shape3_type(TYPE_TRIANGLES);
	sl_shape3_draw(positions, count);
}

void
rvg_triangle_strip3(const float* positions, int count) {
	sl_shape3_type(TYPE_TRIANGLE_STRIP);
	sl_shape3_draw(positions, count);
}

void
rvg_triangle_fan3(const float* positions, int count) {
	sl_shape3_type(TYPE_TRIANGLE_FAN);
	sl_shape3_draw(positions, count);
}

void
rvg_rect3_on_x(float y0, float z0, float y1, float z1, float x, bool filling) {
	if (filling)
	{
		sl_shape3_type(TYPE_TRIANGLES);

		float coords[18] = {
			x, y0, z0,
			x, y0, z1,
			x, y1, z1,

			x, y1, z1,
			x, y1, z0,
			x, y0, z0,
		};
		sl_shape3_draw(coords, 6);
	}
	else
	{
		sl_shape3_type(TYPE_LINE_STRIP);
		sl_shape3_draw_node(x, y0, z0, true);

 		float coords[12];
 		coords[0] = x; coords[1] = y0; coords[2] = z0;
 		coords[3] = x; coords[4] = y0; coords[5] = z1;
 		coords[6] = x; coords[7] = y1; coords[8] = z1;
 		coords[9] = x; coords[10]= y1; coords[11]= z0;
 		sl_shape3_draw(coords, 4);

		sl_shape3_draw_node(x, y0, z0, false);
		sl_shape3_draw_node(x, y0, z0, true);
	}
}

void
rvg_rect3_on_y(float x0, float z0, float x1, float z1, float y, bool filling) {
	if (filling)
	{
		sl_shape3_type(TYPE_TRIANGLES);

		float coords[18] = {
			x0, y, z0,
			x1, y, z0,
			x1, y, z1,

			x1, y, z1,
			x0, y, z1,
			x0, y, z0,
		};
		sl_shape3_draw(coords, 6);
	}
	else
	{
		sl_shape3_type(TYPE_LINE_STRIP);
		sl_shape3_draw_node(x0, y, z0, true);

 		float coords[12];
 		coords[0] = x0; coords[1] = y; coords[2] = z0;
 		coords[3] = x1; coords[4] = y; coords[5] = z0;
 		coords[6] = x1; coords[7] = y; coords[8] = z1;
 		coords[9] = x0; coords[10]= y; coords[11]= z1;
 		sl_shape3_draw(coords, 4);

		sl_shape3_draw_node(x0, y, z0, false);
		sl_shape3_draw_node(x0, y, z0, true);
	}
}

void
rvg_rect3_on_z(float x0, float y0, float x1, float y1, float z, bool filling) {
	if (filling)
	{
		sl_shape3_type(TYPE_TRIANGLES);

		float coords[18] = {
			x0, y0, z,
			x1, y0, z,
			x1, y1, z,

			x1, y1, z,
			x0, y1, z,
			x0, y0, z,
		};
		sl_shape3_draw(coords, 6);
	}
	else
	{
		sl_shape3_type(TYPE_LINE_STRIP);
		sl_shape3_draw_node(x0, y0, z, true);

 		float coords[12];
 		coords[0] = x0; coords[1] = y0; coords[2] = z;
 		coords[3] = x1; coords[4] = y0; coords[5] = z;
 		coords[6] = x1; coords[7] = y1; coords[8] = z;
 		coords[9] = x0; coords[10]= y1; coords[11]= z;
 		sl_shape3_draw(coords, 4);

		sl_shape3_draw_node(x0, y0, z, false);
		sl_shape3_draw_node(x0, y0, z, true);
	}
}

#ifdef _MSC_VER
#	include <malloc.h>
#	define ARRAY(type, name, size) type* name = (type*)_alloca((size) * sizeof(type))
#else
#	define ARRAY(type, name, size) type name[size]
#endif

void
rvg_circle3(float x, float y, float z, float radius, bool filling, int segments) {
	const float k_increment = 2.0f * PI / segments;
	float theta = 0.0f;
	if (!filling) {
		sl_shape3_type(TYPE_LINE_STRIP);
		sl_shape3_draw_node(x + radius, y, z, true);
		ARRAY(float, coords, segments * 3 + 3);
		int ptr = 0;
		for (int i = 0; i <= segments; ++i) {
			coords[ptr++] = x + cosf(theta) * radius;
			coords[ptr++] = y + sinf(theta) * radius;
			coords[ptr++] = z;
			theta += k_increment;
		}
		sl_shape3_draw(coords, segments + 1);
		sl_shape3_draw_node(x + radius, y, z, true);
	} else {
		sl_shape3_type(TYPE_TRIANGLE_STRIP);
		int ptr = 0;
		sl_shape3_draw_node(x, y, z, true);
		sl_shape3_draw_node(x, y, z, true);
		ARRAY(float, coords, (segments + 1) * 6);
		for (int i = 0; i <= segments; ++i) {
			coords[ptr++] = x + cosf(theta) * radius;
			coords[ptr++] = y + sinf(theta) * radius;
			coords[ptr++] = z;
			coords[ptr++] = x;
			coords[ptr++] = y;
			coords[ptr++] = z;
			theta += k_increment;
		}
		sl_shape3_draw(coords, (segments + 1) * 2);
		sl_shape3_draw_node(x, y, z, true);
		sl_shape3_draw_node(x, y, z, true);
	}
}