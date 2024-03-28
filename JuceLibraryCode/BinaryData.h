/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Figma_Plugin_Background_png;
    const int            Figma_Plugin_Background_pngSize = 67182;

    extern const char*   Knob1_png;
    const int            Knob1_pngSize = 157087;

    extern const char*   Knob2_png;
    const int            Knob2_pngSize = 418660;

    extern const char*   clipperPluginBackground2_png;
    const int            clipperPluginBackground2_pngSize = 204928;

    extern const char*   InstantClipperBackground_png;
    const int            InstantClipperBackground_pngSize = 24568;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
