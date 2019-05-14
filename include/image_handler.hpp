#include <wx/image.h>
#include "utils.hpp"

//number of Landsat bands to work with
#define N 8




enum 
{
    CA = 0,
    B  = 1,
    G  = 2,
    R  = 3,
    NIR = 4,
    SWIR1 = 5,
    SWIR2 = 6,
    PC    = 7
};





class ImageHandler
{
    private:
        wxImage* image;
        //Landsat Bands
        wxImage*        BANDS[N] = {NULL, NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        
        std::string     paths[N] = {"","","","","","","",""};
        int             width;
        int             height;

        Color           colors[256];
        
        
        void            LoadPalette(const char* palette);     
        wxImage*        GenerateCommonFormulaIndexImage(std::string band1, std::string band2);
    public:
        ImageHandler();
        
        
        
        void            AddImagePath(std::string path);
        void            SetImagePath(std::string path, int index);
        void            ResetImagePaths();
        wxImage*        GetImage();
        
        
        wxImage*        GetRGBImage();
        wxImage*        ComputeNDVI();
        wxImage*        ComputeNDWI();
        
        /*
        wxImage* GenerateImage(wxImage* red, wxImage* green, wxImage* blue);

        wxImage* ComputeNDVI(wxImage* red, wxImage* infrared);

        wxImage* ComputeColoredNDVI(wxImage* red, wxImage* infrared);

        wxImage* ComputeNDWI(wxImage* infrared, wxImage* mirinfrared);

        wxImage*  ComputeColoredNDWI(wxImage* infrared, wxImage* mirinfrared);

        wxImage* ComputeIndex(wxImage* list[], char* str);

        wxImage* ComputeColoredIndex(wxImage* list[], char* str);

        void LoadPalette();
        */
};



//"Hello World, Where there is will, there is a way."
