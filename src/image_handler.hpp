#include <wx/image.h>

//number of Landsat bands to work with
#define N 8


typedef struct
{
  unsigned char B, G, R;
} RgbPixel;


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
        int width;
        int height;

        RgbPixel colors[256];
    public:
        ImageHandler();
        
        
        
        void AddImagePath(std::string path);
        void SetImagePath(std::string path, int index);
        void ResetImagePaths();
        void LoadPalette();
        wxImage* GetImage(); 
        
        
        wxImage* GetRGBImage();
        wxImage* ComputeNDVI();
        
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
