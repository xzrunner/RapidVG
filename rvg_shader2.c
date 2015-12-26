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

static void
_commit() {
	struct render_buffer * rb = &(RS->vb);
	if (rb->object == 0)
		return;

	struct render *R = RS->R;
	render_buffer_update(R, RS->vertex_buffer, rb->vb, 4 * rb->object);
	renderbuffer_commit(rb);

	rb->object = 0;
}

void 
rvg_shader2_init() {
	S.shader = sl_shader_load(shader_vert, shader_frag);

	sl_shader_create_vertex_buffer(S.shader, MAX_VERTEX, sizeof(struct vertex));

	struct vertex_attrib va[2] = {
		{ "position", 0, 2, sizeof(float), BUFFER_OFFSET(vx) },
		{ "color", 0, 4, sizeof(uint8_t), BUFFER_OFFSET(color) },
	};
	sl_shader_create_vertex_layout(S.shader, sizeof(va)/sizeof(va[0]), va);

	

// 	rvg_shader_init();
// 	rvg_shader_load();
}