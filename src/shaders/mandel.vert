R"(
#version 460 core
layout (location = 0) in vec2 vertex_pos;
layout (location = 1) in vec2 vertex_uv;
layout (location = 2) in vec4 vertex_color;
layout (location = 3) in vec3 vertex_cmix;
// out vec2 uv;
out vec2 pos;
out vec4 color;
// out vec3 cmix;

uniform mat4 projection;
void main()
{
    // uv = vertex_uv;
    pos = vertex_pos;
    color = vertex_color;
    // cmix = vertex_cmix;
    gl_Position = projection * vec4(vertex_pos.xy, 0.0, 1.0);
}
)"