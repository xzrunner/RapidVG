#include "rvg_render.h"
#include "rvg_shader.h"
#include "rvg_math.h"

#include <gl/glew.h>

static int CIRCLE_SEGMENTS = 16;

void 
rvg_point(float x, float y, float size) {
	rvg_shader_type(TYPE_POINTS);

	glPointSize(size);

	float coords[2];
	coords[0] = x;
	coords[1] = y;
	rvg_shader_add_vertices(coords, 1);
}

void 
rvg_line(float x0, float y0, float x1, float y1) {
	rvg_shader_type(TYPE_LINES);
	
	float coords[4];
	coords[0] = x0;
	coords[1] = y0;
	coords[2] = x1;
	coords[3] = y1;
	rvg_shader_add_vertices(coords, 2);	
}

void 
rvg_rect(float xmin, float ymin, float xmax, float ymax, bool filling) {
	if (filling) {
		rvg_shader_type(TYPE_QUADS);
	} else {
		rvg_shader_type(TYPE_LINE_LOOP);
	}

 	float coords[8];
 	coords[0] = xmin; coords[1] = ymin;
 	coords[2] = xmax; coords[3] = ymin;
 	coords[4] = xmax; coords[5] = ymax;
 	coords[6] = xmin; coords[7] = ymax;
 	rvg_shader_add_vertices(coords, 4);
}

void 
rvg_set_circle_segments(int segments) {
	CIRCLE_SEGMENTS = segments;
}

void 
rvg_circle(float x, float y, float radius, bool filling) {
	const float k_increment = 2.0f * PI / CIRCLE_SEGMENTS;
	float theta = 0.0f;
	if (!filling) {
		rvg_shader_type(TYPE_LINE_LOOP);
		float coords[CIRCLE_SEGMENTS * 2];
		int ptr = 0;
		for (int i = 0; i < CIRCLE_SEGMENTS; ++i) {
			coords[ptr++] = x + cosf(theta) * radius;
			coords[ptr++] = y + sinf(theta) * radius;
			theta += k_increment;
		}
		rvg_shader_add_vertices(coords, CIRCLE_SEGMENTS);
	} else {
		rvg_shader_type(TYPE_TRIANGLE_FAN);
		float coords[CIRCLE_SEGMENTS * 2 + 4];
		int ptr = 0;
		coords[ptr++] = x;
		coords[ptr++] = y;
		for (int i = 0; i < CIRCLE_SEGMENTS; ++i) {
			coords[ptr++] = x + cosf(theta) * radius;
			coords[ptr++] = y + sinf(theta) * radius;
			theta += k_increment;
		}
		coords[ptr++] = coords[2];
		coords[ptr++] = coords[3];
		rvg_shader_add_vertices(coords, CIRCLE_SEGMENTS + 2);
	}
}