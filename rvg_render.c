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
rvg_point(float x, float y) {
	sl_shape_type(TYPE_POINTS);

	float coords[2];
	coords[0] = x;
	coords[1] = y;
	sl_shape_draw(coords, 1);
}

void 
rvg_line(float x0, float y0, float x1, float y1) {
	sl_shape_type(TYPE_LINES);
	
	float coords[4];
	coords[0] = x0;
	coords[1] = y0;
	coords[2] = x1;
	coords[3] = y1;
	sl_shape_draw(coords, 2);	
}

void 
rvg_lines(const float* positions, int count) {
	sl_shape_type(TYPE_LINES);
	sl_shape_draw(positions, count);
}

void 
rvg_polyline(const float* positions, int count, bool loop) {
	if (count < 2) {
		return;
	}

	sl_shape_type(TYPE_LINE_STRIP);
	sl_shape_draw_node(positions[0], positions[1], true);
	sl_shape_draw(positions, count);
	if (loop) {
		sl_shape_draw_node(positions[0], positions[1], false);
		sl_shape_draw_node(positions[0], positions[1], true);
	} else {
		sl_shape_draw_node(positions[(count - 1) * 2], positions[(count - 1) * 2 + 1], true);
	}
}

void 
rvg_triangles(const float* positions, int count) {
	sl_shape_type(TYPE_TRIANGLES);
	sl_shape_draw(positions, count);
}

void 
rvg_triangle_strip(const float* positions, int count) {
	sl_shape_type(TYPE_TRIANGLE_STRIP);
	sl_shape_draw(positions, count);
}

void 
rvg_rect(float xmin, float ymin, float xmax, float ymax, bool filling) {
	if (filling) {
		sl_shape_type(TYPE_QUADS);
	} else {
		sl_shape_type(TYPE_LINE_STRIP);
		sl_shape_draw_node(xmin, ymin, true);
	}

 	float coords[8];
 	coords[0] = xmin; coords[1] = ymin;
 	coords[2] = xmax; coords[3] = ymin;
 	coords[4] = xmax; coords[5] = ymax;
 	coords[6] = xmin; coords[7] = ymax;
 	sl_shape_draw(coords, 4);

	if (!filling) {
		sl_shape_draw_node(xmin, ymin, false);
		sl_shape_draw_node(xmin, ymin, true);
	}
}

void 
rvg_circle(float x, float y, float radius, bool filling, int segments) {
	const float k_increment = 2.0f * PI / segments;
	float theta = 0.0f;
	if (!filling) {
		sl_shape_type(TYPE_LINE_STRIP);
		sl_shape_draw_node(x + radius, y, true);
		float coords[segments * 2 + 2];
		int ptr = 0;
		for (int i = 0; i <= segments; ++i) {
			coords[ptr++] = x + cosf(theta) * radius;
			coords[ptr++] = y + sinf(theta) * radius;
			theta += k_increment;
		}
		sl_shape_draw(coords, segments + 1);
		sl_shape_draw_node(x + radius, y, true);
	} else {
		sl_shape_type(TYPE_TRIANGLE_STRIP);
		int ptr = 0;
		sl_shape_draw_node(x, y, true);
		sl_shape_draw_node(x, y, true);
		if (segments & 0x1) {
			float coords[segments * 3 + 3];
			for (int i = 0; i < segments; i += 2) {
				coords[ptr++] = x;
				coords[ptr++] = y;
				coords[ptr++] = x + cosf(theta) * radius;
				coords[ptr++] = y + sinf(theta) * radius;
				theta += k_increment;
				coords[ptr++] = x + cosf(theta) * radius;
				coords[ptr++] = y + sinf(theta) * radius;
				theta += k_increment;
			}
			sl_shape_draw(coords, (segments * 3 + 3) / 2);
		} else {
			float coords[segments * 3 + 4];
			for (int i = 0; i < segments; i += 2) {
				coords[ptr++] = x;
				coords[ptr++] = y;
				coords[ptr++] = x + cosf(theta) * radius;
				coords[ptr++] = y + sinf(theta) * radius;
				theta += k_increment;
				coords[ptr++] = x + cosf(theta) * radius;
				coords[ptr++] = y + sinf(theta) * radius;
				theta += k_increment;
			}
			coords[ptr++] = x;
			coords[ptr++] = y;
			coords[ptr++] = x + radius;
			coords[ptr++] = y;
			sl_shape_draw(coords, segments * 3 / 2 + 2);
		}
		sl_shape_draw_node(x + radius, y, true);
		sl_shape_draw_node(x + radius, y, true);
	}
}