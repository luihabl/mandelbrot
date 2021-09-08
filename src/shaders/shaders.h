#pragma once
#include <string>

#include <map>

namespace MB {
    std::map<std::string, std::string>& get_colormaps();
    const char* get_frag_src();
    const char* get_vertex_src();

}


