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



typedef struct
{
  unsigned char B, G, R;
} RgbPixel;

class ImageHandler
{
private:
    wxImage* Image;
    //wxImage* Bands[10];

    int width;
    int height;

    RgbPixel colors[256];
public:
    ImageHandler();

    wxImage* GenerateImage(wxImage* red, wxImage* green, wxImage* blue);

    wxImage* ComputeNDVI(wxImage* red, wxImage* infrared);

    wxImage* ComputeColoredNDVI(wxImage* red, wxImage* infrared);

    wxImage* ComputeNDWI(wxImage* infrared, wxImage* mirinfrared);

    wxImage*  ComputeColoredNDWI(wxImage* infrared, wxImage* mirinfrared);

    wxImage* ComputeIndex(wxImage* list[], char* str);

    wxImage* ComputeColoredIndex(wxImage* list[], char* str);

    void LoadPalette();
};



//"Hello World, Where there is will, there is a way."