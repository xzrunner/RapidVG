#include "rvg_style.h"

#include <c_wrap_sl.h>
#include <c_wrap_ur.h>

struct state {
	enum RVG_LINE_STYLE line_style;
};

static struct state S;

void 
rvg_style_init() {
	S.line_style = LS_DEFAULT;
}

void 
rvg_point_size(float size) {
	void* rc = sl_get_render_context();
	ur_set_point_size(rc, size);
}

void 
rvg_line_width(float width) {
	void* rc = sl_get_render_context();
	ur_set_line_width(rc, width);	
}

void 
rvg_line_style(enum RVG_LINE_STYLE ls) {    
	if (S.line_style == ls) {
		return;
	}

	void* rc = sl_get_render_context();

	sl_flush();

	ur_enable_line_stripple(rc, ls != LS_DEFAULT);

	switch (ls) {
	case LS_DOT:
		ur_set_line_stripple(rc, 0x0101);
		break;
	case LS_DASH:
		ur_set_line_stripple(rc, 0x00FF);
		break;
	case LS_DOT_DASH:
		ur_set_line_stripple(rc, 0x1c47);
		break; 
	}

	S.line_style = ls;
  }