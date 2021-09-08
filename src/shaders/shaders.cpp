#include "shaders.h"

#include <map>

namespace MB
{
    namespace 
    {
        
        std::vector<ColorMapSrc> colormaps = 
        {
            // {"gnuplot",
            // #include "colormaps/gnuplot.frag"
            // },
            {"Spectral",
            #include "colormaps/Spectral.frag"
            },
            {"IDL_16_Level",
            #include "colormaps/IDL_16_Level.frag"
            },
            {"IDL_Beach",
            #include "colormaps/IDL_Beach.frag"
            },
            {"IDL_Black-White_Linear",
            #include "colormaps/IDL_Black-White_Linear.frag"
            },
            {"IDL_Blue-Green-Red-Yellow",
            #include "colormaps/IDL_Blue-Green-Red-Yellow.frag"
            },
            {"IDL_Blue-Pastel-Red",
            #include "colormaps/IDL_Blue-Pastel-Red.frag"
            },
            {"IDL_Blue-Red",
            #include "colormaps/IDL_Blue-Red.frag"
            },
            {"IDL_Blue-Red_2",
            #include "colormaps/IDL_Blue-Red_2.frag"
            },
            {"IDL_Blue-White_Linear",
            #include "colormaps/IDL_Blue-White_Linear.frag"
            },
            {"IDL_Blue_Waves",
            #include "colormaps/IDL_Blue_Waves.frag"
            },
            {"IDL_CB-Accent",
            #include "colormaps/IDL_CB-Accent.frag"
            },
            {"IDL_CB-Blues",
            #include "colormaps/IDL_CB-Blues.frag"
            },
            {"IDL_CB-BrBG",
            #include "colormaps/IDL_CB-BrBG.frag"
            },
            {"IDL_CB-BuGn",
            #include "colormaps/IDL_CB-BuGn.frag"
            },
            {"IDL_CB-BuPu",
            #include "colormaps/IDL_CB-BuPu.frag"
            },
            {"IDL_CB-Dark2",
            #include "colormaps/IDL_CB-Dark2.frag"
            },
            {"IDL_CB-GnBu",
            #include "colormaps/IDL_CB-GnBu.frag"
            },
            {"IDL_CB-Greens",
            #include "colormaps/IDL_CB-Greens.frag"
            },
            {"IDL_CB-Greys",
            #include "colormaps/IDL_CB-Greys.frag"
            },
            {"IDL_CB-Oranges",
            #include "colormaps/IDL_CB-Oranges.frag"
            },
            {"IDL_CB-OrRd",
            #include "colormaps/IDL_CB-OrRd.frag"
            },
            {"IDL_CB-Paired",
            #include "colormaps/IDL_CB-Paired.frag"
            },
            {"IDL_CB-Pastel1",
            #include "colormaps/IDL_CB-Pastel1.frag"
            },
            {"IDL_CB-Pastel2",
            #include "colormaps/IDL_CB-Pastel2.frag"
            },
            {"IDL_CB-PiYG",
            #include "colormaps/IDL_CB-PiYG.frag"
            },
            {"IDL_CB-PRGn",
            #include "colormaps/IDL_CB-PRGn.frag"
            },
            {"IDL_CB-PuBu",
            #include "colormaps/IDL_CB-PuBu.frag"
            },
            {"IDL_CB-PuBuGn",
            #include "colormaps/IDL_CB-PuBuGn.frag"
            },
            {"IDL_CB-PuOr",
            #include "colormaps/IDL_CB-PuOr.frag"
            },
            {"IDL_CB-PuRd",
            #include "colormaps/IDL_CB-PuRd.frag"
            },
            {"IDL_CB-Purples",
            #include "colormaps/IDL_CB-Purples.frag"
            },
            {"IDL_CB-RdBu",
            #include "colormaps/IDL_CB-RdBu.frag"
            },
            {"IDL_CB-RdGy",
            #include "colormaps/IDL_CB-RdGy.frag"
            },
            {"IDL_CB-RdPu",
            #include "colormaps/IDL_CB-RdPu.frag"
            },
            {"IDL_CB-RdYiBu",
            #include "colormaps/IDL_CB-RdYiBu.frag"
            },
            {"IDL_CB-RdYiGn",
            #include "colormaps/IDL_CB-RdYiGn.frag"
            },
            {"IDL_CB-Reds",
            #include "colormaps/IDL_CB-Reds.frag"
            },
            {"IDL_CB-Set1",
            #include "colormaps/IDL_CB-Set1.frag"
            },
            {"IDL_CB-Set2",
            #include "colormaps/IDL_CB-Set2.frag"
            },
            {"IDL_CB-Set3",
            #include "colormaps/IDL_CB-Set3.frag"
            },
            {"IDL_CB-Spectral",
            #include "colormaps/IDL_CB-Spectral.frag"
            },
            {"IDL_CB-YIGn",
            #include "colormaps/IDL_CB-YIGn.frag"
            },
            {"IDL_CB-YIGnBu",
            #include "colormaps/IDL_CB-YIGnBu.frag"
            },
            {"IDL_CB-YIOrBr",
            #include "colormaps/IDL_CB-YIOrBr.frag"
            },
            {"IDL_Eos_A",
            #include "colormaps/IDL_Eos_A.frag"
            },
            {"IDL_Eos_B",
            #include "colormaps/IDL_Eos_B.frag"
            },
            {"IDL_Green-Pink",
            #include "colormaps/IDL_Green-Pink.frag"
            },
            {"IDL_Green-Red-Blue-White",
            #include "colormaps/IDL_Green-Red-Blue-White.frag"
            },
            {"IDL_Green-White_Exponential",
            #include "colormaps/IDL_Green-White_Exponential.frag"
            },
            {"IDL_Green-White_Linear",
            #include "colormaps/IDL_Green-White_Linear.frag"
            },
            {"IDL_Hardcandy",
            #include "colormaps/IDL_Hardcandy.frag"
            },
            {"IDL_Haze",
            #include "colormaps/IDL_Haze.frag"
            },
            {"IDL_Hue_Sat_Lightness_1",
            #include "colormaps/IDL_Hue_Sat_Lightness_1.frag"
            },
            {"IDL_Hue_Sat_Lightness_2",
            #include "colormaps/IDL_Hue_Sat_Lightness_2.frag"
            },
            {"IDL_Hue_Sat_Value_1",
            #include "colormaps/IDL_Hue_Sat_Value_1.frag"
            },
            {"IDL_Hue_Sat_Value_2",
            #include "colormaps/IDL_Hue_Sat_Value_2.frag"
            },
            {"IDL_Mac_Style",
            #include "colormaps/IDL_Mac_Style.frag"
            },
            {"IDL_Nature",
            #include "colormaps/IDL_Nature.frag"
            },
            {"IDL_Ocean",
            #include "colormaps/IDL_Ocean.frag"
            },
            {"IDL_Pastels",
            #include "colormaps/IDL_Pastels.frag"
            },
            {"IDL_Peppermint",
            #include "colormaps/IDL_Peppermint.frag"
            },
            {"IDL_Plasma",
            #include "colormaps/IDL_Plasma.frag"
            },
            {"IDL_Prism",
            #include "colormaps/IDL_Prism.frag"
            },
            {"IDL_Purple-Red+Stripes",
            #include "colormaps/IDL_Purple-Red+Stripes.frag"
            },
            {"IDL_Rainbow+Black",
            #include "colormaps/IDL_Rainbow+Black.frag"
            },
            {"IDL_Rainbow+White",
            #include "colormaps/IDL_Rainbow+White.frag"
            },
            {"IDL_Rainbow",
            #include "colormaps/IDL_Rainbow.frag"
            },
            {"IDL_Rainbow_18",
            #include "colormaps/IDL_Rainbow_18.frag"
            },
            {"IDL_Rainbow_2",
            #include "colormaps/IDL_Rainbow_2.frag"
            },
            {"IDL_Red-Purple",
            #include "colormaps/IDL_Red-Purple.frag"
            },
            {"IDL_Red_Temperature",
            #include "colormaps/IDL_Red_Temperature.frag"
            },
            {"IDL_Standard_Gamma-II",
            #include "colormaps/IDL_Standard_Gamma-II.frag"
            },
            {"IDL_Steps",
            #include "colormaps/IDL_Steps.frag"
            },
            {"IDL_Stern_Special",
            #include "colormaps/IDL_Stern_Special.frag"
            },
            {"IDL_Volcano",
            #include "colormaps/IDL_Volcano.frag"
            },
            {"IDL_Waves",
            #include "colormaps/IDL_Waves.frag"
            },
            {"kbinani_altitude",
            #include "colormaps/kbinani_altitude.frag"
            },
            {"MATLAB_autumn",
            #include "colormaps/MATLAB_autumn.frag"
            },
            {"MATLAB_bone",
            #include "colormaps/MATLAB_bone.frag"
            },
            {"MATLAB_cool",
            #include "colormaps/MATLAB_cool.frag"
            },
            {"MATLAB_copper",
            #include "colormaps/MATLAB_copper.frag"
            },
            {"MATLAB_hot",
            #include "colormaps/MATLAB_hot.frag"
            },
            {"MATLAB_hsv",
            #include "colormaps/MATLAB_hsv.frag"
            },
            {"MATLAB_jet",
            #include "colormaps/MATLAB_jet.frag"
            },
            // {"MATLAB_parula",
            // #include "colormaps/MATLAB_parula.frag"
            // },
            // {"MATLAB_pink",
            // #include "colormaps/MATLAB_pink.frag"
            // },
            {"MATLAB_spring",
            #include "colormaps/MATLAB_spring.frag"
            },
            {"MATLAB_summer",
            #include "colormaps/MATLAB_summer.frag"
            },
            {"MATLAB_winter",
            #include "colormaps/MATLAB_winter.frag"
            },
            {"transform_apricot",
            #include "colormaps/transform_apricot.frag"
            },
            {"transform_carnation",
            #include "colormaps/transform_carnation.frag"
            },
            {"transform_ether",
            #include "colormaps/transform_ether.frag"
            },
            {"transform_grayscale_banded",
            #include "colormaps/transform_grayscale_banded.frag"
            },
            {"transform_hot_metal",
            #include "colormaps/transform_hot_metal.frag"
            },
            {"transform_lava_waves",
            #include "colormaps/transform_lava_waves.frag"
            },
            {"transform_malachite",
            #include "colormaps/transform_malachite.frag"
            },
            {"transform_morning_glory",
            #include "colormaps/transform_morning_glory.frag"
            },
            {"transform_peanut_butter_and_jerry",
            #include "colormaps/transform_peanut_butter_and_jerry.frag"
            },
            {"transform_purple_haze",
            #include "colormaps/transform_purple_haze.frag"
            },
            {"transform_rainbow",
            #include "colormaps/transform_rainbow.frag"
            },
            {"transform_rose",
            #include "colormaps/transform_rose.frag"
            },
            {"transform_saturn",
            #include "colormaps/transform_saturn.frag"
            },
            {"transform_seismic",
            #include "colormaps/transform_seismic.frag"
            },
            {"transform_space",
            #include "colormaps/transform_space.frag"
            },
            {"transform_supernova",
            #include "colormaps/transform_supernova.frag"
            }
        };

            const char* vertex_src =
            #include "mandel.vert"
            ;

            const char* frag_src =
            #include "mandel.frag"
            ;
    }

    std::vector<ColorMapSrc>& get_colormaps()
    {
        return colormaps;
    }

    const char* get_frag_src()
    {
        return frag_src;
    }

    const char* get_vertex_src()
    {
        return vertex_src;
    }




}