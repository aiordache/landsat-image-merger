#include <math.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "image_handler.hpp"

using namespace std;
using namespace cv;



ImageHandler::ImageHandler()
{
    //the current processed image
    image = NULL;
    
    //load default color scheme from file
    FILE *fp;
    fp = fopen("resources/colors.pal", "r");

    if(fp == NULL)
    {
        printf("file not found!\n");
        exit(0);
    }
    else
    {
        int i = 0, j = 0;
        int index = 0, r = 0, g = 0, b=0;
        while(!feof(fp))
        {
            fscanf(fp, "%d", &index);
            fscanf(fp, "%d", &r);
            fscanf(fp, "%d", &g);
            fscanf(fp, "%d", &b);
            defcolors[index].B = b;
            defcolors[index].G = g;
            defcolors[index].R = r;
        }
        fclose(fp) ;
    }
    
    colors = defcolors;
    
    cout<<"Pointer address: "<<colors<<" is default "<<defcolors<<endl;
}

void ImageHandler::AddImagePath(string path)
{
    cout<<"Add path : "<<path<<endl;
    int i = 0;
    while(paths[i] != "" && i < N)
        i++;
    if (i >= 0 && i < N)    
        paths[i] = path;
}

void ImageHandler::SetImagePath(string path, int index)
{
    cout<<" Set image path: "<<path<<" at "<<index<<endl; 
    paths[index] = path;
}

void ImageHandler::ResetImagePaths()
{
    for (int i = 0; i < N; i++)
        paths[i].clear();
    if (image)  free(image);
    image = NULL;

}

void ImageHandler::ResetColorPalette()
{
    if (colors != NULL && colors != defcolors)
        free(colors);
    colors = defcolors;
}
wxImage* ImageHandler::GetColorPaletteImage()
{
    if (palette != NULL)
        return palette;
    
    UpdateColorPaletteImage();
    return palette;
}

void ImageHandler::UpdateColorPaletteImage()
{
    if (palette != NULL)
        delete palette;
    
    int width = 256;
    int height = 20;
    
    palette = new wxImage(width, height,(unsigned char*)malloc(width * height *3), false);

    
    for(int i = 0; i < width * height; i++)
    {
        palette->GetData()[i * 3]     = (unsigned char)colors[i % width].R;
        palette->GetData()[i * 3 + 1] = (unsigned char)colors[i % width].G;
        palette->GetData()[i * 3 + 2] = (unsigned char)colors[i % width].B;
    }
    
}

void ImageHandler::LoadColorPalette(unsigned int color1, unsigned int color2)
{
    ResetColorPalette();
    
    
    vector<unsigned int> rgb1 = {(color1 & 0x00ff0000) >> 16, (color1 & 0x0000ff00) >> 8, (color1 & 0x000000ff)};
    vector<unsigned int> rgb2 = {(color2 & 0x00ff0000) >> 16, (color2 & 0x0000ff00) >> 8, (color2 & 0x000000ff)};
    
    if (colors != defcolors)
        delete colors;
    colors = new Color[256];
    cout<<"Pointer address: "<<colors<<" default: "<<defcolors<<endl;
    
    for(int i = 0; i < 256; i++)
    {   
        
        float r = interpolate((float)rgb1[0], (float)rgb2[0], i);
        float g = interpolate((float)rgb1[1], (float)rgb2[1], i);
        float b = interpolate((float)rgb1[2], (float)rgb2[2], i);
        
        cout <<r<<"  "<<g<<"  "<<b<<endl;  
        
        colors[i].R = (unsigned char) r;
        colors[i].G = (unsigned char) g;
        colors[i].B = (unsigned char) b;
        
        cout << i<<" "<<(int)colors[i].R<< " "<<(int)colors[i].G<<" "<<(int)colors[i].R<<endl;
    }
    
    UpdateColorPaletteImage();
}


wxImage* ImageHandler::GetImage()
{
    return image;
};


wxImage* ImageHandler::GetRGBImage()
{
    if (paths[R] == "" || paths[G] == "" || paths[B] == "")
        return NULL;
    
    Mat blue  = imread(paths[B], CV_8UC1);
    Mat green = imread(paths[G], CV_8UC1);
    Mat red   = imread(paths[R], CV_8UC1);
    
    vector<Mat> channels = {blue, green, red};
    Mat color(blue.size(), CV_8UC3);
    
    merge(channels, color);
    //imwrite("merged.png", color);
    cvtColor(color, color, COLOR_BGR2RGB);
    
    long size = color.cols * color.rows * 3;
    
    if(image != NULL) free(image);
    
    image = new wxImage(color.cols, color.rows,(unsigned char*)malloc(size), false);
    memcpy(image->GetData(), color.data, size);
	
    return image;
}

wxImage* ImageHandler::GenerateCommonFormulaIndexImage(std::string band1, std::string band2)
{
    /*
        Several indexes are calculated using the formula
        INDEX = (B1 - B2)/(B1 + B2)
    */
    Mat B1   = imread(band1, CV_8UC1);
    Mat B2   = imread(band2, CV_8UC1);        
    
    if (B1.size() != B2.size())
        return NULL;
    
    Mat img = Mat::zeros(B1.size(), CV_8UC3);
    
    long size = B1.cols * B1.rows;
    for(int i = 0; i < size; i++)
    {
        float value = (B1.data[i] == B2.data[i]) ? 0 : (float)(B1.data[i] - B2.data[i])/(float)(B1.data[i] + B2.data[i]);
        // transform from [-1, 1] to [0, 255]
        unsigned char color = (unsigned char)128 * value + 128; 
        
        img.data[i * 3] = (unsigned char)(colors[color].B);
        img.data[i * 3 + 1] = (unsigned char)(colors[color].G);
        img.data[i * 3 + 2] = (unsigned char)(colors[color].R);
    }
    
    imwrite("index.png", img);
    cvtColor(img, img, COLOR_BGR2RGB); 
      
    size = size * 3;
        
    if(image != NULL) free(image);
    
    image = new wxImage(img.cols, img.rows,(unsigned char*)malloc(size), false);
    memcpy(image->GetData(), img.data, size);
	
    return image;
}



wxImage* ImageHandler::ComputeNDVI()
{
    /*
        Normalized Difference Vegetation Index (NDVI) uses the NIR and red channels in its formula.
        NDVI = (NIR - RED)/(NIR + RED)
    */
    
    return GenerateCommonFormulaIndexImage(paths[NIR], paths[R]);
}




wxImage* ImageHandler::ComputeNDWI()
{
    /*
    Normalized Difference Water Index (NDWI), introduced for the first time in 1996 in Gao (Gao), reflects moisture content in plants and soil and is determined by analogy with NDVI as

    NDWI = (NIR - SWIR)/(NIR + SWIR)
    */
    return GenerateCommonFormulaIndexImage(paths[NIR], paths[SWIR1]);
}







/*

    wxImage* ComputeIndex(wxImage* list[], char* str)
    {
        int n = 0, k = 0;

        n = strlen(str);
        wxImage* img = GenerateImage(wxSize(list[0]->GetWidth(), list[0]->GetHeight()),IPL_DEPTH_32F,1);

        int index = 0;
        for (int i = 0; i < img->GetHeight(); i++)
        {
            unsigned char k1 = 0;
            unsigned char* row[7];

            while(list[k1]!= 0)
            {
                row[k1] = &CV_IMAGE_ELEM(list[k1], unsigned char, i, 0 );
                k1++;
            }
            for( int j = 0; j < img->GetWidth(); j++)
            {
                float value[20];

                index = 0;
                int index = 0;

                k = 0;
                while(k < n)
                {
                    switch(str[k])
                    {
                        case '+':
                            {
                                value[index - 2] = value[index - 1] + value[index - 2];
                                index = index - 1;
                                break;
                            }
                        case '-':
                            {
                                value[index - 2] = value[index - 1] - value[index - 2];
                                index = index - 1;
                                break;
                            }
                        case '*':
                            {
                                value[index - 2] = value[index - 1] * value[index - 2];
                                index = index - 1;
                                break;
                            }
                        case '/':
                            {
                                value[index - 2] =(float) 128 + 128*(value[index - 1] / (float)value[index - 2]);
                                index = index - 1;
                                break;
                            }
                        case 'b':
                            {
                                value[index] = (float)(row[(int)(str[k + 1] - '0')][j]);
                                k++;
                                index++;
                                break;
                            }
                        default:
                            {

                                float no = 0.0;
                                int x = k;
                                while(str[x] >= '0' && str[x] <= '9')
                                x++;
                                //form the scalar from string
                                for(int q = k; q < x; q++)
                                    no = no * 10 + (str[q] - '0');

                                value[index] = no;
                                index++;
                                break;
                            }
                    }
                    k++;
                }
                ((float*)img->m_refData)[i * img->GetWidth() + j] = value[index - 1];
            }
        }
        wxImage* Image = GenerateImage(wxSize(img->GetWidth(), img->GetHeight()),CV_DEPTH_MAX,1);

        cvConvertScale(img, Image, 1, 0);

        return Image;
    }

*/



//"Hello World, Where there is will, there is a way."
