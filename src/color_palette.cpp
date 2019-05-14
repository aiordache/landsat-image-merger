#include "color_palette.hpp"

using namespace std;

ColorPalette::ColorPalette()
{
    
}
void ColorPalette::AddColor(Color color)
{
    pivotcolors.push_back(color);
}

void ColorPalette::AddColor(Color color, unsigned char index)
{
    if (index < pivotcolors.size())
        pivotcolors[index] = color;
    else
        pivotcolors.push_back(color);
}

Color* ColorPalette::GenerateRGBPalette()
{
    static Color palette[256];
    
    return palette;
}
