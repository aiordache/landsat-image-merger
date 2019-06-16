#include <math.h>
#include <iostream>
#include <unordered_map>
#include <opencv2/imgcodecs.hpp>

#include <pthread.h>
#include "image_handler.hpp"
#include "eval.hpp"


#define UIntToRGB(x) { (float)(x & 0x000000ff), (float)((x & 0x0000ff00) >> 8), (float)((x & 0x00ff0000) >> 16)}


using namespace std;
using namespace cv;

static float MAX;
static float MIN;

typedef struct arguments {
    long start;
    long end;
    unordered_map<string, Mat> bandmap;
    Eval F;
    wxImage* image;
    float min;
    float max;
    Color* colors;
} Args;


static void combinations(Eval F, vector<string> params, vector<int> allowed_values, vector<int> values, int n) 
{
	if (n == 0)
	{
	    unordered_map<string, float> input;
	    for(int i = 0; i < values.size(); i++)
		    input[params[i]] = values[i];
		float y = F(input);
		if (y > MAX)
		    MAX = y;
		else if (y < MIN)
		    MIN = y;
		return; 
	} 
	for (int i = 0; i < allowed_values.size(); i++) 
	{
	    vector<int> x = values;
	    x.push_back(allowed_values[i]);
		combinations(F, params, allowed_values, x, n - 1);  
	}
}

void* split_work(void* arg)
{
   Args* p = (Args*)arg;
   
   unordered_map<string, float> values;
   for(long i = p->start; i < p->end; i++)
    {
        
        for (auto item : p->bandmap) 
            values[item.first] = (float)item.second.data[i];
        float value = p->F(values);
        
        // transform from [min, max] to [0, 255]
        unsigned char color = (unsigned char)(value * 255.f/(MAX - MIN)); 
        
        p->image->GetData()[i * 3]     = (unsigned char)p->colors[color].R;
        p->image->GetData()[i * 3 + 1] = (unsigned char)p->colors[color].G;
        p->image->GetData()[i * 3 + 2] = (unsigned char)p->colors[color].B;
    }
    
    return NULL;
}  

ImageHandler::ImageHandler()
{
    
    for(int i = 0;i < N; i++)
        paths[i]   = "";
        
    message = new wxString("No Landsat band loaded.");
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
}

ImageHandler::~ImageHandler()
{
    if (image != NULL) delete image;
    if (message != NULL) delete message;
}

bool ImageHandler::AddImagePath(string path)
{
    int i = 0;
    while(paths[i] != "" && i < N)
        i++;
    if (i >= 0 && i < N)    
    {
        paths[i] = path;
        bands[i] = imread(paths[i], CV_8UC1);
        if (bands[i].data == NULL)
        {
            if (message != NULL) delete message;
            message = new wxString( wxT("Failed to load band: ") + paths[i]);
            paths[i] = "";
            return false;
        }
    }
    if (message != NULL) delete message;
    message = NULL;
    return true;
}

bool ImageHandler::SetImagePath(string path, int index)
{ 
    paths[index] = path;
    bands[index] = imread(path, CV_8UC1);
    
    if (message != NULL) delete message;
    message = NULL;
    
    if (bands[index].data == NULL)
    {
        message = new wxString(wxT("Failed to load band: ") + paths[index]);
        paths[index] = "";
        return false;
    }
    return true;
}

void ImageHandler::ResetImagePaths()
{
    for (int i = 0; i < N; i++)
    {
        if (paths[i] != "")
            bands[i].release();
        paths[i].clear();
    }
    if (image)  delete image;
    image = NULL;
    
    if (message != NULL) delete message;
    message = new wxString("No Landsat band loaded. Use menu buttons to load them.");
}

void ImageHandler::ResetColorPalette()
{
    if (colors != NULL && colors != defcolors)
        delete colors;
    colors = defcolors;
    UpdateColorPaletteImage();
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

void ImageHandler::LoadColorPalette(std::vector<unsigned int> colorlist)
{
    int stripe = 255 / (colorlist.size() - 1);
    
    ResetColorPalette();
    
    if (colors != defcolors)
        delete colors;
        
    colors = new Color[255];
    
    int k = 0;
    // keep BLACK as first color always
    colors[0].R = 0;
    colors[0].G = 0;
    colors[0].B = 0;
    
    
    for(int i = 0; i < 255; i++)
    {
        k = i / stripe;   
        
        float rgb1[3] = UIntToRGB(colorlist[k]);
        float rgb2[3] = UIntToRGB(colorlist[k + 1]);
        
        for(int j = 0; j < 3; j++)
        {
            float p = (i % stripe)/(float)stripe;
            float value = (1.0f - p) * rgb1[j] + (p * rgb2[j]) + 0.01f;
            switch(j)
            {
                case 0:  colors[i + 1].R = (unsigned char) value; break;
                case 1:  colors[i + 1].G = (unsigned char) value; break;
                case 2:  colors[i + 1].B = (unsigned char) value; 
            };
        }
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
    {
        if (message != NULL) delete message;
        message = new wxString("One or more RGB bands not loaded.");
        return NULL;
    }
    Mat blue  = bands[B];
    Mat green = bands[G];
    Mat red   = bands[R];
    
    vector<Mat> channels = {blue, green, red};
    Mat color(blue.size(), CV_8UC3);
    
    merge(channels, color);
    cvtColor(color, color, COLOR_BGR2RGB);
    
    long size = color.cols * color.rows * 3;
    
    if(image != NULL) delete image;
    
    image = new wxImage(color.cols, color.rows,(unsigned char*)malloc(size), false);
    memcpy(image->GetData(), color.data, size);
	
    return image;
}

wxImage* ImageHandler::GenerateCommonFormulaIndexImage(int band1, int band2)
{
    /*
        Several indexes are calculated using the formula
        INDEX = (B1 - B2)/(B1 + B2)
    */
    if (paths[band1] == "" || paths[band2] == "")
    {
        if (message != NULL) delete message;
        message = new wxString("Targeted bands not loaded.");
        
        return NULL;    
    }
    
    Mat B1   = bands[band1];
    Mat B2   = bands[band2];        
    
    if (B1.size() != B2.size())
    {
        if (message != NULL) delete message;
        message = new wxString("Check the bands loaded. Different size detected.");
        return NULL;
    }
    Mat img = Mat::zeros(B1.size(), CV_8UC3);
    
    long size = B1.cols * B1.rows;
    for(int i = 0; i < size; i++)
    {
        unsigned char color = 0;
        if (B1.data[i] != 0 || B2.data[i] != 0)
        {   
            float value = (B1.data[i] == B2.data[i]) ? 0 : (float)(B1.data[i] - B2.data[i])/(float)(B1.data[i] + B2.data[i]);
            // transform from [-1, 1] to [0, 255]
            color = (unsigned char)128 * value + 128; 
        }
        img.data[i * 3] = (unsigned char)(colors[color].B);
        img.data[i * 3 + 1] = (unsigned char)(colors[color].G);
        img.data[i * 3 + 2] = (unsigned char)(colors[color].R);
    }
    
    cvtColor(img, img, COLOR_BGR2RGB); 
      
    size = size * 3;
        
    if(image != NULL) delete image;
    
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
    
    return GenerateCommonFormulaIndexImage(NIR, R);
}


wxImage* ImageHandler::ComputeNDWI()
{
    /*
        Normalized Difference Water Index (NDWI) reflects moisture content in plants and soil
        NDWI = (NIR - SWIR)/(NIR + SWIR)
    */
    return GenerateCommonFormulaIndexImage(NIR, SWIR1);
}


wxImage* ImageHandler::ComputeCustomIndex(string expr)
{
    if (!IsValidExpr(expr))
    {
        if (message != NULL) delete message;
        message = new wxString("Invalid expression.");
        return NULL;
    }
    
    vector<int> bindex;
    unordered_map<string, Mat> varmap;
    for(int i = 0; i < exprvar.size(); i++)
    {
        string s = exprvar[i].substr(0,  string::npos);
        bindex.push_back(stoi(s.erase(0, 1)) - 1);
        if (bindex[i] < 0 || bindex[i] > N - 1)
        {
            if (message != NULL) delete message;
            message = new wxString("Invalid expression.");
            return NULL;
        }
    }
    if (bindex.size() == 0)
    {
        if (message != NULL) delete message;
        message = new wxString("Invalid expression.");
        return NULL;
    }
    
    CalculateInterval(expr);
    
    Eval eval(expr);
    
    float min = interval[0];
    float max = interval[1];
    
    for(int j = 0; j < bindex.size();j++)
    {
        if (paths[bindex[j]] == "")
        {
            if (message != NULL) delete message;
            message = new wxString("Targeted bands not loaded.");
            return NULL;
        }
        varmap[exprvar[j]] = bands[bindex[j]];
    }
    Size size = bands[bindex[0]].size();
    
    if (image != NULL) delete image;
        
    image = new wxImage(size.width, size.height,(unsigned char*)malloc(size.width * size.height *3), false);
    
    int T = 100;
    pthread_t threads[T];

    long stripe = size.width * size.height/ T;
    
    Args* a[T];
    
    for(int i = 0; i < T; i++) 
    {  
        a[i] = new Args({i*stripe, i < T -1 ? (i+1) * stripe : size.width * size.height, varmap, eval, image, min, max, colors});
        
        if(pthread_create(&threads[i], NULL, &split_work, (void*)a[i]) != 0) 
        {
            if (message != NULL) delete message;
            message = new wxString("Error creating thread.");
            return NULL;
        }
    }
    for(int i = 0; i < T; i++)   
    {  
        if(pthread_join(threads[i], NULL))
        {
            if (message != NULL) delete message;
            message = new wxString("Error joining thread.");
            return NULL;
        }
        delete a[i];
    }
    return image;
}

bool ImageHandler::IsOperator(char c)
{
    switch(c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')': return true;
        default: return false;
    }
}
bool ImageHandler::IsValidExpr(string expr)
{
   //check if expression is valid
    int brackets = 0;
    
    int i = 0, j = 0;
    //check brackets first and remove them
    string str;
    for(i = 0; i <expr.size(); i++)
    {
        if (brackets < 0)
            break;
        if (expr[i] == '(')
        {
            brackets++;
            continue;
        }
        else if (expr[i] == ')')
        {
            brackets--;
            continue;
        }
        str += expr[i];
    }
    if (brackets != 0 || IsOperator(str[0]) || IsOperator(str[str.size() - 1]))
        return false;
    
    bool valid   = true;
    exprvar.clear();
    
    i = 0;
    j = 0;
    while(i < str.size())
    {
        while (j < str.size()) 
        {
            if (IsOperator(str[j]))    
                break;
            j++;
        }
        
        if (j  < str.size() && i == j)
        {
            valid = false;
            break;
        }
        
        bool var_b = false;
        if(str[i] == 'b' || str[i] == 'B')
        {
            var_b = true;
            i++;
        }           
        string s = str.substr(i, j - i);
        int x = stoi(s);
        if (to_string(x) != s)
        {
            valid = false;
            break;
        }
        else 
        if (var_b && x >N && x <= 0)
        {
            valid = false;
            break;
        }
        else
            if (var_b)
            {
                string value = str.substr(i - 1, j - i + 1);
                if (find(exprvar.begin(), exprvar.end(), value) == exprvar.end())
                    exprvar.push_back(value);
            }
        j++;
        i = j;
    }
    if (!valid || brackets != 0)
        return false;
    return true;
}


void ImageHandler::CalculateInterval(string expr)
{
    Eval eval(expr);
    
    MAX=MIN=0;
    
    combinations(eval, exprvar, {0, 255}, {}, exprvar.size());
    
    interval[0] = MIN;
    interval[1] = MAX;
}

wxString* ImageHandler::GetMessage()
{
    return message;
}


