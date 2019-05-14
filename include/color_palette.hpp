#include <vector>
#include "utils.hpp"

class ColorPalette
{
    private:
    
        unsigned char         num;
        std::vector<Color> pivotcolors;
        
    public:
        ColorPalette();
        
        void    AddColor(Color color);
        void    AddColor(Color color, unsigned char index);
        Color*  GenerateRGBPalette();

};
