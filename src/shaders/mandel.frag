R"(
#version 460 core

precision highp float;

// in vec2 uv;
in vec2 pos;
in vec4 color;
// in vec3 cmix;
out vec4 output_color;

uniform float zoom;
uniform vec2 offset;
uniform vec2 window_size;

#define MAX_ITERATIONS 100 // 500


int get_iterations()
{
    float real = (pos.x / zoom) + offset.x; 
    float imag = (pos.y / zoom) + offset.y; 
 
    int iterations = 0;
    float const_real = real;
    float const_imag = imag;
 
    while (iterations < MAX_ITERATIONS)
    {
        float tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        float dist = real * real + imag * imag;
         
        if (dist > 4.0)
        break;
 
        ++iterations;
    }
    return iterations;
}

vec4 calc_color()
{
    int iter = get_iterations();
    if (iter == MAX_ITERATIONS)
    {
        // gl_FragDepth = 0.0f;
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
 
    float iterations = float(iter) / MAX_ITERATIONS;    
    return vec4(iterations, iterations, 2 * iterations, 1.0f);
}

// uniform sampler2D image;
void main()
{
    //vec4 tex_color = texture(image, uv);
    //output_color = tex_color * color * cmix.x + tex_color.a * color * cmix.y + color * cmix.z;
    // float xx = (pos.x / zoom) + offset.x;// xy[0];
    // float yy = (pos.y / zoom) + offset.y;

    // vec2 world_pos = (pos / zoom) + offset; 

    // float x = grid(world_pos, 0.1f); // resolution
    // output_color.rgb = vec3(0.5) * x;  
    // output_color.a = 1.0;

    output_color = calc_color();


}
)"