/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_127183451_INCLUDED
#define BINARYDATA_H_127183451_INCLUDED

namespace BinaryData
{
    extern const char*   panel_overlays_png;
    const int            panel_overlays_pngSize = 4694;

    extern const char*   knob_overlay_png;
    const int            knob_overlay_pngSize = 454;

    extern const char*   slider_overlay_png;
    const int            slider_overlay_pngSize = 303;

    extern const char*   a_png;
    const int            a_pngSize = 243;

    extern const char*   amp_title_png;
    const int            amp_title_pngSize = 535;

    extern const char*   cutoff_png;
    const int            cutoff_pngSize = 449;

    extern const char*   d_png;
    const int            d_pngSize = 232;

    extern const char*   filter_title_png;
    const int            filter_title_pngSize = 583;

    extern const char*   gain_png;
    const int            gain_pngSize = 404;

    extern const char*   logo_png;
    const int            logo_pngSize = 908;

    extern const char*   osc_title_png;
    const int            osc_title_pngSize = 547;

    extern const char*   r_png;
    const int            r_pngSize = 248;

    extern const char*   res_png;
    const int            res_pngSize = 373;

    extern const char*   s_png;
    const int            s_pngSize = 272;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 14;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
