R"(
#version 460 core
in vec2 uv;
in vec4 color;
in vec3 cmix;
out vec4 output_color;
uniform sampler2D image;
void main()
{
    vec4 tex_color = texture(image, uv);
    output_color = tex_color * color * cmix.x + tex_color.a * color * cmix.y + color * cmix.z;
}
)"