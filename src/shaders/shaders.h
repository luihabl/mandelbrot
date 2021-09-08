#pragma once
#include <string>

#include <vector>

namespace MB {
    struct ColorMapSrc
    {
        const char* label;
        const char* src;
        ColorMapSrc(const char* _label, const char* _src) : label(_label), src(_src) {}
    };

    std::vector<ColorMapSrc>& get_colormaps();
    const char* get_frag_src();
    const char* get_vertex_src();

}


