R"(
#version 460 core
// in vec2 uv;
in vec2 pos;
in vec4 color;
// in vec3 cmix;
out vec4 output_color;

uniform float zoom;
uniform vec2 offset;
uniform vec2 window_size;


float grid(vec2 st, float res)
{
  vec2 grid = fract(st*res);
  return (step(res,grid.x) * step(res,grid.y));
}

// uniform sampler2D image;
void main()
{
    //vec4 tex_color = texture(image, uv);
    //output_color = tex_color * color * cmix.x + tex_color.a * color * cmix.y + color * cmix.z;
    // float xx = (pos.x / zoom) + offset.x;// xy[0];
    // float yy = (pos.y / zoom) + offset.y;

    vec2 world_pos = (pos / zoom) + offset; 

    float x = grid(world_pos, 0.1f); // resolution
    output_color.rgb = vec3(0.5) * x;  
    output_color.a = 1.0;
}
)"