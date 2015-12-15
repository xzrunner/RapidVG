#ifdef __cplusplus
extern "C"
{
#endif

#ifndef rapid_vector_graphics_shader_h
#define rapid_vector_graphics_shader_h

void rvg_shader_init();

void rvg_shader_load();
void rvg_shader_unload();

void rvg_shader_bind();
void rvg_shader_unbind();

void rvg_shader_projection(int width, int height);
void rvg_shader_modelview(float x, float y, float sx, float sy);

void rvg_shader_type(int type);

void rvg_shader_color(int color);

void rvg_shader_add_vertices(float* coords, int count);

void rvg_shader_flush();

#endif // rapid_vector_graphics_shader_h

#ifdef __cplusplus
}
#endif