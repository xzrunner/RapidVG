#ifdef __cplusplus
extern "C"
{
#endif

#ifndef rapid_vector_graphics_render3_h
#define rapid_vector_graphics_render3_h

#include <stdbool.h>

void rvg_point3(float x, float y, float z);

void rvg_line3(float x0, float y0, float z0, float x1, float y1, float z1);
void rvg_lines3(const float* positions, int count);
void rvg_polyline3(const float* positions, int count, bool loop);

void rvg_triangles3(const float* positions, int count);
void rvg_triangle_strip3(const float* positions, int count);

void rvg_rect3(float xmin, float ymin, float xmax, float ymax, float z, bool filling);

void rvg_circle3(float x, float y, float z, float radius, bool filling, int segments);

#endif // rapid_vector_graphics_render3_h

#ifdef __cplusplus
}
#endif