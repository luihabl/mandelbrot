R"(
#version 460 core
#define ADDITIONAL_ITER 1

precision highp float;

in vec2 pos;
in vec4 color;
out vec4 output_color;

uniform double zoom;
uniform dvec2 offset;
uniform dvec2 window_size;

uniform int min_iter_range;
uniform int max_iter_range;

uniform double radius;
uniform float scale_exp;

vec4 colormap(float x);

double get_iterations()
{
    dvec2 dpos = dvec2(pos);
    double real = (dpos.x / zoom) + offset.x; 
    double imag = (dpos.y / zoom) + offset.y; 
 
    uint iterations = 0;
    double const_real = real;
    double const_imag = imag;

    double dist = 0.0;
 
    while (iterations < max_iter_range)
    {
        double tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        dist = real * real + imag * imag;
         
        if (dist > radius)
        break;
 
        ++iterations;
    }

    
    for(int i = 0; i < ADDITIONAL_ITER; i++)
    {
        double tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        dist = real * real + imag * imag;
          
        ++iterations;
    }

    float modulus = sqrt(float(dist));
    float mu = float(iterations) + 1.0f - (log2(log(modulus)));
    return double(mu);
}

void main()
{
    double iter = get_iterations();

    iter = clamp(iter, min_iter_range + ADDITIONAL_ITER, max_iter_range + ADDITIONAL_ITER);
    


    
    float it = pow(float(iter - double(min_iter_range + ADDITIONAL_ITER)) / float(max_iter_range - min_iter_range), scale_exp);
    // it = clamp(it, 0, 1);

    output_color = colormap(it);
}

)"