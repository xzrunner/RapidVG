#include "rvg_style.h"

#include <opengl.h>

#include "c_wrap_sl.h"

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
#ifndef __APPLE__
	glPointSize(size);
#endif
}

void 
rvg_line_width(float width) {
	glLineWidth(width);
}

void 
rvg_line_style(enum RVG_LINE_STYLE ls) {
#ifndef __APPLE__
    
	if (S.line_style == ls) {
		return;
	}

	sl_flush();

	if (ls == LS_DEFAULT) {
		glDisable(GL_LINE_STIPPLE);
	} else {
		glEnable(GL_LINE_STIPPLE);
	}

	switch (ls) {
	case LS_DOT:
		glLineStipple(1, 0x0101);
		break;
	case LS_DASH:
		glLineStipple(1, 0x00FF);
		break;
	case LS_DOT_DASH:
		glLineStipple(1, 0x1c47);
		break; 
	}

	S.line_style = ls;
    
#endif
}