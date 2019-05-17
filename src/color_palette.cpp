#include <wx/brush.h>
#include <wx/graphics.h>
#include "color_palette.hpp"

using namespace std;

IMPLEMENT_DYNAMIC_CLASS(ColorPalette, wxControl);


BEGIN_EVENT_TABLE(ColorPalette, wxControl)
	EVT_PAINT(ColorPalette::OnPaint)
END_EVENT_TABLE()

ColorPalette::ColorPalette (wxWindow* parent, wxWindowID id, const wxString& txt) : wxControl (parent, id) 
{ 
    SetLabel(txt); 
    SetSize(230,30);
    SetWindowStyle(0);
}

void ColorPalette::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	wxCoord x = 0,y = 0,width = 0,height = 0,tw = 0,th = 0;

	GetClientSize( &width, &height );

	if (bitmap != NULL)
	    dc.DrawBitmap(*bitmap, 0, 0);
	    
	if (!IsEnabled())
	{ 
	    wxGraphicsContext *gc = wxGraphicsContext::Create( dc );
        if (gc)
        {
            gc->SetBrush(wxBrush(wxColour(250,250,250,128)));
            gc->DrawRectangle(0,0,width, height);
            delete gc;
        }
	}
}


void ColorPalette::CreatePaletteBitmap()
{
    int width = GetSize().GetWidth();
    int height = GetSize().GetHeight();
    wxImage img(width, height);
    
    int n = pickedcolors.size();
    int  square = width / n;
    for(int i = 0; i < width * height ; i++)
    {
        int x = i % width;
        int y = i / width;
        int p = x % square;
        int col_index = x/square;
        if (x >1 && x < width - 6 && y >1 && y < height - 6 && p > 1 && p < square - 1)
        {
            unsigned char r = pickedcolors[col_index] & 0x000000ff;
            unsigned char g = (pickedcolors[col_index]& 0x0000ff00) >> 8;
            unsigned char b = (pickedcolors[col_index] & 0x00ff0000) >> 16;
            
            img.GetData()[i* 3]    = r;
            img.GetData()[i*3 + 1] = g;
            img.GetData()[i*3 + 2] = b;
        }
        else
        {
            img.GetData()[i*3]     = 255;
            img.GetData()[i*3 + 1] = 255;
            img.GetData()[i*3 + 2] = 255;
        }
    }
    
    bitmap = new wxBitmap(img);
}

void ColorPalette::SetColorCount(int num)
{
    int i = pickedcolors.size();
    if (pickedcolors.size() < num)
    {
        while(i < num)
        {
            pickedcolors.push_back(0);
            i++;
        }
    }
    else
    {
        while(i > num)
        {
            pickedcolors.pop_back();
            i--;
        }
     }
     CreatePaletteBitmap();
        Refresh();
}

void ColorPalette::SetColor(int index, unsigned int color)
{


}


	    

