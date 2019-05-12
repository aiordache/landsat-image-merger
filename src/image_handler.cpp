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
}

wxImage* ImageHandler::GetRGBImage()
{
    if (paths[R] == "" || paths[G] == "" || paths[B] == "")
        return NULL;
    
    Mat blue  = imread(paths[B], IMREAD_GRAYSCALE);
    Mat green = imread(paths[G], IMREAD_GRAYSCALE);
    Mat red   = imread(paths[R], IMREAD_GRAYSCALE);
    
    vector<Mat> channels = {blue, green, red};

    Mat bgr;
    merge(channels, bgr);
    //imwrite("merged.png", bgr);
    
    long size = bgr.cols * bgr.rows * 3;
    if(image != NULL) free(image);
    image = new wxImage(bgr.cols, bgr.rows,(unsigned char*)malloc(size), false);
	unsigned char* src  = bgr.data;
	unsigned char* dest = image->GetData();
	for (long i = 0; i < size; i=i+3) 
	{ 
	    dest[i] = src[i+2];
	    dest[i+1] = src[i+1];
	    dest[i+2] = src[i];
	}
	
    return image;
    
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
void ImageHandler::SaveImage(string path)
{
    cout<<"Saving image to "<<path<<" .... ";
    
    /*Mat im2(Size(wx.GetWidth(),wx.GetHeight()),CV_8UC3,wx.GetData());
    cvtColor(im2,im2,COLOR_RGB2BGR);
    return im2;
    
    imwrite(path, image);*/
};
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
        fp = fopen("NDVI_DOS.pal", "r");

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
