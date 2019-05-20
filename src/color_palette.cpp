#include <wx/brush.h>
#include <wx/graphics.h>
#include <wx/colordlg.h>

#include "color_palette.hpp"

using namespace std;

wxDEFINE_EVENT(COLOR_SELECTED, wxCommandEvent);

IMPLEMENT_DYNAMIC_CLASS(ColorPalette, wxControl);

BEGIN_EVENT_TABLE(ColorPalette, wxControl)
	EVT_PAINT(ColorPalette::OnPaint)
	EVT_LEFT_UP(ColorPalette::OnMouseClick) 
	EVT_MOTION(ColorPalette::OnMouseHover)
	EVT_LEAVE_WINDOW(ColorPalette::OnMouseLeave)
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
	
	if (IsEnabled() && (focus < 0))
	    return;
	    
    wxGraphicsContext *gc = wxGraphicsContext::Create( dc );
    if (gc)
    {
        if (!IsEnabled())
        {
            gc->SetBrush(wxBrush(wxColour(250,250,250,128)));
            gc->DrawRectangle(0,0,width, height);
        }
        else
	    {
	        gc->SetBrush(wxColour(0,0,128,128));
            gc->SetPen(*wxBLACK_PEN);
	        gc->DrawRectangle(focus*pwidth - padding, 0, pwidth + padding, height);
	    }
    
        delete gc;
    }
}

void ColorPalette::OnMouseLeave(wxMouseEvent& event)
{
    focus = -1;
    Refresh();
}

void ColorPalette::OnMouseHover(wxMouseEvent& event)
{
    int mouseX = event.GetX();
    int mouseY = event.GetY();
    
    int index = (mouseX % GetSize().GetWidth())/pwidth;
    
    if (index != focus && index < pickedcolors.size())
    {
        focus = index;
        Refresh();
    }
}

void ColorPalette::OnMouseClick(wxMouseEvent& event)
{
    int mouseX = event.GetX();
    int mouseY = event.GetY();
    
    wxColourDialog dlg(this);

    if (dlg.ShowModal() == wxID_OK)
    {
        wxColour c = dlg.GetColourData().GetColour();
        
        int index = (mouseX % GetSize().GetWidth())/pwidth;
        pickedcolors[index] = (unsigned int)c.GetRGB();
        CreatePaletteBitmap();
        focus = -1;
        Refresh();
    }
    
}


void ColorPalette::CreatePaletteBitmap()
{
    int width = GetSize().GetWidth();
    int height = GetSize().GetHeight();
    wxImage img(width, height);
    
    int n = pickedcolors.size();
    
    padding = 20/n;
    //must draw n color partitions 
    //pwidth - width of each partition
    pwidth = width/n;
    
    for(int i = 0; i < width * height ; i++)
    {
        int x = i % width;
        int y = i / width;
        int col_index = x/pwidth;
        //cout<<x<<" "<<y<< "   COL :"<<col_index<< " LEN:"<<p<<endl; 
        if ((x >=padding && x < width - padding) &&  // check left and right padding
            (y>=2 && y < height-6)&& // fixed small padding for top and bottom
            (x % pwidth < pwidth - padding && col_index < n))
        {
            unsigned int color = pickedcolors[col_index];
            unsigned char r = color & 0x000000ff;
            unsigned char g = (color & 0x0000ff00) >> 8;
            unsigned char b = (color & 0x00ff0000) >> 16;
            
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
    
    // fire event
    wxCommandEvent event(COLOR_SELECTED, GetId());
    event.SetEventObject(this);
    ProcessWindowEvent(event);
}

void ColorPalette::SetColorCount(int num)
{
    int i = pickedcolors.size();
    if (i < num)
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
vector<unsigned int> ColorPalette::GetColorList()
{
    return pickedcolors;
}

	    

