#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <wx/image.h>

/* get reference to pixel at (col,row),
   for multi-channel images (col) should be multiplied by number of channels */
#define CV_IMAGE_ELEM( image, elemtype, row, col )       \
    (((elemtype*)((image)->m_refData + (image)->widthStep*(row)))[(col)])

// ...

#define CV_MAT_ELEM_PTR_FAST( mat, row, col, pix_size )  \
    (assert( (unsigned)(row) < (unsigned)(mat).rows &&   \
             (unsigned)(col) < (unsigned)(mat).cols ),   \
     (mat).data.ptr + (size_t)(mat).step*(row) + (pix_size)*(col))

#define CV_MAT_ELEM_PTR( mat, row, col )                 \
    CV_MAT_ELEM_PTR_FAST( mat, row, col, CV_ELEM_SIZE((mat).type) )

#define CV_MAT_ELEM( mat, elemtype, row, col )           \
    (*(elemtype*)CV_MAT_ELEM_PTR_FAST( mat, row, col, sizeof(elemtype)))

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
        wxImage* Image;
        //Landsat Bands
        wxImage*        BANDS[N] = {NULL, NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        
        std::string     paths[N] = {"","","","","","","",""};
        int width;
        int height;

        RgbPixel colors[256];
    public:
        ImageHandler();
        
        wxImage* GetRGBImage();
        
        
        void AddImagePath(std::string path);
        void SetImagePath(std::string path, int index);
        void ResetImagePaths();
        void SaveImage(std::string path);
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
