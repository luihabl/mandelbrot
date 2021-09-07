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

uniform int max_iter = 200;
uniform double radius = 4.0;
uniform float scale_exp = 0.5f;

vec4 spectral_color(float l) // RGB <0,1> <- lambda l <400,700> [nm]
{
    float t, r=0.0f, g=0.0f, b=0.0f;
         if ((l>=400.0)&&(l<410.0)) { t=(l-400.0)/(410.0-400.0); r=    +(0.33*t)-(0.20*t*t); }
    else if ((l>=410.0)&&(l<475.0)) { t=(l-410.0)/(475.0-410.0); r=0.14         -(0.13*t*t); }
    else if ((l>=545.0)&&(l<595.0)) { t=(l-545.0)/(595.0-545.0); r=    +(1.98*t)-(     t*t); }
    else if ((l>=595.0)&&(l<650.0)) { t=(l-595.0)/(650.0-595.0); r=0.98+(0.06*t)-(0.40*t*t); }
    else if ((l>=650.0)&&(l<700.0)) { t=(l-650.0)/(700.0-650.0); r=0.65-(0.84*t)+(0.20*t*t); }
         if ((l>=415.0)&&(l<475.0)) { t=(l-415.0)/(475.0-415.0); g=             +(0.80*t*t); }
    else if ((l>=475.0)&&(l<590.0)) { t=(l-475.0)/(590.0-475.0); g=0.8 +(0.76*t)-(0.80*t*t); }
    else if ((l>=585.0)&&(l<639.0)) { t=(l-585.0)/(639.0-585.0); g=0.84-(0.84*t)           ; }
         if ((l>=400.0)&&(l<475.0)) { t=(l-400.0)/(475.0-400.0); b=    +(2.20*t)-(1.50*t*t); }
    else if ((l>=475.0)&&(l<560.0)) { t=(l-475.0)/(560.0-475.0); b=0.7 -(     t)+(0.30*t*t); }

    return vec4(r, g, b, 1.0f);
}

double get_iterations()
{
    dvec2 dpos = dvec2(pos);
    double real = (dpos.x / zoom) + offset.x; 
    double imag = (dpos.y / zoom) + offset.y; 
 
    uint iterations = 0;
    double const_real = real;
    double const_imag = imag;

    double dist = 0.0;
 
    while (iterations < max_iter)
    {
        double tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        dist = real * real + imag * imag;
         
        if (dist > radius)
        break;
 
        ++iterations;
    }

    
    for(int i = 0; i<2; i++)
    {
        double tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        dist = real * real + imag * imag;
          
        ++iterations;
    }



    float modulus = sqrt(float(dist));
    float mu = float(iterations) + 1 - (log(log(modulus)) / log(2.0));



    return double(mu);
}

vec4 calc_color()
{
    double iter = get_iterations();
    if (iter == (max_iter+2))
    {
        // gl_FragDepth = 0.0f;
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
 
    float it = float(iter) / float(max_iter+2);    
    
    return(spectral_color( 400.0+(300.0*pow(it, scale_exp)) ));
    // return vec4(iterations, iterations, 2 * iterations, 1.0f);
}

// uniform sampler2D image;
void main()
{
    output_color = calc_color();
}
)"