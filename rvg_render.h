#ifdef __cplusplus
extern "C"
{
#endif

#ifndef rapid_vector_graphics_render_h
#define rapid_vector_graphics_render_h

#include <stdbool.h>

void rvg_point(float x, float y);

void rvg_line(float x0, float y0, float x1, float y1);
void rvg_lines(const float* positions, int count);
void rvg_polyline(const float* positions, int count, bool loop);

void rvg_triangles(const float* positions, int count);

void rvg_rect(float xmin, float ymin, float xmax, float ymax, bool filling);

void rvg_circle(float x, float y, float radius, bool filling, int segments);

#endif // rapid_vector_graphics_render_h

#ifdef __cplusplus
}
#endif