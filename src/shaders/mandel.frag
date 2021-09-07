R"(
#version 460 core

precision highp float;

// in vec2 uv;
in vec2 pos;
in vec4 color;
// in vec3 cmix;
out vec4 output_color;

uniform double zoom;
uniform dvec2 offset;
uniform dvec2 window_size;

#define MAX_ITERATIONS 500 // 500


uint get_iterations()
{
    dvec2 dpos = dvec2(pos);
    double real = (dpos.x / zoom) + offset.x; 
    double imag = (dpos.y / zoom) + offset.y; 
 
    uint iterations = 0;
    double const_real = real;
    double const_imag = imag;
 
    while (iterations < MAX_ITERATIONS)
    {
        double tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        double dist = real * real + imag * imag;
         
        if (dist > 4.0)
        break;
 
        ++iterations;
    }
    return iterations;
}

vec4 calc_color()
{
    uint iter = get_iterations();
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
    output_color = calc_color();
}
)"