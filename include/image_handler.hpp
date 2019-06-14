#include <wx/image.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <stack>

#define N 12

typedef struct
{
  unsigned char R, G, B;
} Color;



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
    
        std::vector<std::string>     exprvar;
        wxImage*                     image = NULL;
        wxString*                    message = NULL;
        //Landsat Bands
        cv::Mat         bands[N];
        std::string     paths[N];
        int             interval[2] = {0, 255};
        int             width;
        int             height;
        
        Color           defcolors[256];
        Color           *colors = NULL;
        wxImage         *palette = NULL;   
        wxImage*        GenerateCommonFormulaIndexImage(int band1, int band2);
        void            UpdateColorPaletteImage();
        bool            IsOperator(char c);
        
        bool            IsValidExpr(std::string expr);
        void            CalculateInterval(std::string expr);
        
    public:
        ImageHandler();
        ~ImageHandler();
        
        bool            AddImagePath(std::string path);
        bool            SetImagePath(std::string path, int index);
        void            ResetImagePaths();
        void            ResetColorPalette();
        void            LoadColorPalette(std::vector<unsigned int> colorlist); 
        wxImage*        GetImage();
        wxImage*        GetColorPaletteImage();
        
        wxImage*        GetRGBImage();
        wxImage*        ComputeNDVI();
        wxImage*        ComputeNDWI();
        wxImage*        ComputeCustomIndex(std::string str);
        
        wxString*       GetMessage();
};


