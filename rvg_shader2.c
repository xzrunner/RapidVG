#include "rvg_shader2.h"

#include <sl_shader.h>
#include <render/render.h>

#include <stdint.h>

#define STRINGIFY(A)  #A
#include "shader.vert"
#include "shader.frag"

#define MAX_VERTEX		1024

#define BUFFER_OFFSET(f) ((intptr_t)&(((struct vertex *)NULL)->f))

struct vertex {
	float vx, vy;
	uint32_t color;
};

struct shader_state {
	int shader;
};

static struct shader_state S;

void 
rvg_shader2_init() {
	int s = sl_shader_load(shader_vert, shader_frag);

	sl_shader_set_draw_mode(s, );

	sl_shader_create_vertex_buffer(s, MAX_VERTEX, sizeof(struct vertex));

	struct vertex_attrib va[2] = {
		{ "position", 0, 2, sizeof(float), BUFFER_OFFSET(vx) },
		{ "color", 0, 4, sizeof(uint8_t), BUFFER_OFFSET(color) },
	};
	sl_shader_create_vertex_layout(s, sizeof(va)/sizeof(va[0]), va);

	

// 	rvg_shader_init();
// 	rvg_shader_load();

	S.shader = s;
}