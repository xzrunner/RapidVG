#ifdef __cplusplus
extern "C"
{
#endif

#ifndef rapid_vector_graphics_render_h
#define rapid_vector_graphics_render_h

#include <stdbool.h>

void rvg_point(float x, float y, float size);

void rvg_line(float x0, float y0, float x1, float y1);

void rvg_rect(float xmin, float ymin, float xmax, float ymax, bool filling);

void rvg_set_circle_segments(int segments);
void rvg_circle(float x, float y, float radius, bool filling);

#endif // rapid_vector_graphics_render_h

#ifdef __cplusplus
}
#endif