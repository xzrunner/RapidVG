#ifdef __cplusplus
extern "C"
{
#endif

#ifndef rapid_vector_graphics_style_h
#define rapid_vector_graphics_style_h

enum RVG_LINE_STYLE
{
	LS_DEFAULT = 0,
	LS_DOT,
	LS_DASH,
	LS_DOT_DASH
};

void rvg_style_init();

void rvg_point_size(float size);

void rvg_line_width(float width);
void rvg_line_style(enum RVG_LINE_STYLE ls);

#endif // rapid_vector_graphics_style_h

#ifdef __cplusplus
}
#endif