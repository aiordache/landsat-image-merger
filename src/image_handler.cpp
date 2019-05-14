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
    LoadPalette();
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

void ImageHandler::LoadPalette()
    {

        FILE *fp;
        fp = fopen("resources/NDVI.pal", "r");

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
                colors[index].B = b;
                colors[index].G = g;
                colors[index].R = r;
            }
            fclose(fp) ;
        }
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

wxImage* ImageHandler::ComputeNDVI()
{
    /*
        Normalized Difference Vegetation Index (NDVI) uses the NIR and red channels in its formula.
        NDVI = (NIR - RED)/(NIR + RED)
    */

    Mat red   = imread(paths[R], CV_8UC1);
    Mat nir   = imread(paths[NIR], CV_8UC1);        
    
    if (red.size() != nir.size())
        return NULL;
    
    Mat ndvi = Mat::zeros(red.size(), CV_8UC3);
    
    long size = red.cols * red.rows;
    for(int i = 0; i < size; i++)
    {
        float value = (nir.data[i] == red.data[i]) ? 0 : (float)(nir.data[i] - red.data[i])/(float)(nir.data[i] + red.data[i]);
        // transform from [-1, 1] to [0, 255]
        unsigned char color = (unsigned char)128 * value + 128; 
        
        ndvi.data[i * 3] = (unsigned char)(colors[color].B);
        ndvi.data[i * 3 + 1] = (unsigned char)(colors[color].G);
        ndvi.data[i * 3 + 2] = (unsigned char)(colors[color].R);
    }
    
    imwrite("ndvi.png", ndvi);
    cvtColor(ndvi, ndvi, COLOR_BGR2RGB); 
      
    size = size * 3;
        
    if(image != NULL) free(image);
    
    image = new wxImage(ndvi.cols, ndvi.rows,(unsigned char*)malloc(size), false);
    memcpy(image->GetData(), ndvi.data, size);
	
    return image;
}













  /*
    wxImage* GenerateImage(wxImage* red, wxImage* green, wxImage* blue)
    {
        int i,j;

        if (Image != 0)
                Image = 0;
        Image = GenerateImage(wxSize(red->GetWidth(), red->GetHeight()),CV_DEPTH_MAX,3);

        cvMerge(blue, green, red, NULL, Image);

        return Image;
    }

    wxImage* ComputeNDVI(wxImage* red, wxImage* infrared)
    {
        int k = 0;
        float f = 0.0;
        int i, j;

        if (Image != 0)
                Image = 0;

        wxImage* ndvi = GenerateImage(wxSize(red->GetWidth(), red->GetHeight()),IPL_DEPTH_32F,1);

        for (i = 0; i < red->GetHeight(); i++)
        {
            unsigned char* row = &CV_IMAGE_ELEM( red, unsigned char, i, 0 );
            unsigned char* roww = &CV_IMAGE_ELEM( infrared, unsigned char, i, 0 );

            for( int j = 0; j < red->GetWidth(); j++)
            {
                f = (float)(roww[j] - row[j])/(float)(row[j] + roww[j]);
                ((float*)ndvi->m_refData)[i *  ndvi->GetWidth() + j] = 128 + 128*f;
            }
        }

        Image = GenerateImage(wxSize(red->GetWidth(), red->GetHeight()),CV_DEPTH_MAX,1);

        cvConvertScale(ndvi, Image, 1, 0);

        return Image;
    }

    wxImage* ComputeColoredNDVI(wxImage* red, wxImage* infrared)
    {
        int k = 0;
        float f = 0.0;
        int i, j;

        LoadPalette();

        if (Image != 0)
                Image = 0;

        Image = GenerateImage(wxSize(red->GetWidth(), red->GetHeight()),CV_DEPTH_MAX,3);

        for (i = 0; i < red->height; i++)
        {
            unsigned char* row = &CV_IMAGE_ELEM( red, unsigned char, i, 0 );
            unsigned char* roww = &CV_IMAGE_ELEM( infrared, unsigned char, i, 0 );
            unsigned char* rowc = &CV_IMAGE_ELEM( Image, unsigned char, i, 0 );

            for( int j = 0; j < red->GetWidth(); j++)
            {
                f = (float)(roww[j] - row[j])/(float)(row[j] + roww[j]);
                rowc[j * 3] = (unsigned char)(colors[(unsigned char)(128 + 128 * f)].B);
                rowc[j * 3 + 1] = (unsigned char)(colors[(unsigned char)(128 + 128 * f)].G);
                rowc[j * 3 + 2] = (unsigned char)(colors[(unsigned char)(128 + 128 * f)].R);
            }
        }

        return Image;
    }

    wxImage* ComputeNDWI(wxImage* infrared, wxImage* mirinfrared)
    {
        int k = 0;
        float f = 0.0;
        int i, j;

        if (Image != 0)
                Image = 0;

        wxImage* ndwi = GenerateImage(wxSize(infrared->GetWidth(), infrared->GetHeight()),IPL_DEPTH_32F,1);

        for (i = 0; i < infrared->GetHeight(); i++)
        {
            unsigned char* row = &CV_IMAGE_ELEM( infrared, unsigned char, i, 0 );
            unsigned char* roww = &CV_IMAGE_ELEM( mirinfrared, unsigned char, i, 0 );

            for( int j = 0; j < infrared->GetWidth(); j++)
            {
                f = (float)(row[j] - roww[j])/(float)(row[j] + roww[j]);
                ((float*)ndwi->m_refData)[i *  ndwi->GetWidth() + j] = 128 + 128*f;
            }
        }

        Image = GenerateImage(wxSize(infrared->GetWidth(), infrared->GetHeight()),CV_DEPTH_MAX,1);

        cvConvertScale(ndwi, Image, 1, 0);

        return Image;
    }

    wxImage*  ComputeColoredNDWI(wxImage* infrared, wxImage* mirinfrared)
    {
        int k = 0;
        float f = 0.0;
        int i, j;

        LoadPalette();

        if (Image != 0)
                Image = 0;
        Image = GenerateImage(wxSize(infrared->GetWidth(), infrared->GetHeight()),CV_DEPTH_MAX, 3);

        for (i = 0; i < infrared->GetHeight(); i++)
        {
            unsigned char* row = &CV_IMAGE_ELEM( infrared, unsigned char, i, 0 );
            unsigned char* roww = &CV_IMAGE_ELEM( mirinfrared, unsigned char, i, 0 );
            unsigned char* rowc = &CV_IMAGE_ELEM( Image, unsigned char, i, 0 );

            for( int j = 0; j < infrared->GetWidth(); j++)
            {
                f = (float)(row[j] - roww[j])/(float)(row[j] + roww[j]);
                rowc[j * 3] = (unsigned char)(colors[(unsigned char)(128 + 128 * f)].B);
                rowc[j * 3 + 1] = (unsigned char)(colors[(unsigned char)(128 + 128 * f)].G);
                rowc[j * 3 + 2] = (unsigned char)(colors[(unsigned char)(128 + 128 * f)].R);
            }
        }

        return Image;
    }

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


    wxImage* ComputeColoredIndex(wxImage* list[], char* str)
    {
        int n = 0;
        n = strlen(str);

        LoadPalette();

        wxImage* Image = GenerateImage(wxSize(list[0]->GetWidth(), list[0]->GetHeight()),CV_DEPTH_MAX,3);

        int index = 0;
        for (int i = 0; i < Image->GetHeight(); i++)
        {
            unsigned char k1 = 0;
            unsigned char* row[7];

            while(list[k1]!= 0)
            {
                row[k1] = &CV_IMAGE_ELEM(list[k1], unsigned char, i, 0 );
                k1++;
            }

            unsigned char* imgrow = &CV_IMAGE_ELEM( Image, unsigned char, i, 0 );

            for( int j = 0; j < Image->GetWidth(); j++)
            {
                float value[20];

                index = 0;
                int index = 0;

                int k = 0;
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
                 imgrow[j * 3] = (unsigned char)(colors[(unsigned char)(value[0])].B);
                 imgrow[j * 3 + 1] = (unsigned char)(colors[(unsigned char)(value[0])].G);
                 imgrow[j * 3 + 2] = (unsigned char)(colors[(unsigned char)(value[0])].R);
            }
        }

        return Image;
    }

    void LoadPalette()
    {

        FILE *fp;
        fp = fopen("resources/NDVI_DOS.pal", "r");

        if(fp == NULL)
        {
            printf("file not found!\n");
            exit(0);
        }
        else
        {
            int i = 0, j = 0;
            int pos = 0, r = 0, g = 0, b=0;
            while(!feof(fp))
            {
                fscanf(fp, "%d", &pos);
                fscanf(fp, "%d", &r);
                fscanf(fp, "%d", &g);
                fscanf(fp, "%d", &b);
                colors[pos].B = b;
                colors[pos].G = g;
                colors[pos].R = r;
            }

            fclose(fp) ;
        }
    }*/



//"Hello World, Where there is will, there is a way."
