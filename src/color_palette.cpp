#include "color_palette.hpp"
using namespace std;

IMPLEMENT_DYNAMIC_CLASS(ColorPalette, wxControl);


BEGIN_EVENT_TABLE(ColorPalette, wxControl)
	EVT_PAINT(ColorPalette::OnPaint)
END_EVENT_TABLE()

ColorPalette::ColorPalette (wxWindow* parent, wxWindowID id, const wxString& txt) : wxControl (parent, id) 
{ 
    SetLabel(txt); 
    SetSize(200,30);
    SetWindowStyle(0);
}

wxSize ColorPalette::DoGetBestSize() const
{
	// Do not return any arbitrary default value...
	wxASSERT_MSG( m_widget, wxT("ColorPalette::DoGetBestSize called before creation") );

	wxClientDC dc (const_cast<ColorPalette*> (this));

	wxCoord w;
	wxCoord h;
	dc.GetTextExtent( "test", &w, &h );

	return wxSize( w, h );
}

void ColorPalette::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	wxCoord x = 0,y = 0,width = 0,height = 0,tw = 0,th = 0;

	GetClientSize( &width, &height );

	dc.SetTextForeground (GetForegroundColour ());
	dc.SetTextBackground (GetBackgroundColour ());

	if (bitmap != NULL)
	    dc.DrawBitmap(*bitmap, 0, 0);
}

void ColorPalette::SetLabel( const wxString& label )
{
	wxControl::SetLabel( label );
	Refresh ();
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
        
        if (x >1 && x < width - 6 && y >1 && y < height - 6 && p > 1 && p < square - 1)
        {
            img.GetData()[i* 3]     = 0;
            img.GetData()[i*3 + 1] = 0;
            img.GetData()[i*3 + 2] = 0;
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
    if (pickedcolors.size() < num)
    {
        int i = pickedcolors.size();
        while(i < num)
        {
            pickedcolors.push_back(0);
            i++;
        }
        CreatePaletteBitmap();
        Refresh();
    }
}

void ColorPalette::SetColot(int index, unsigned int color)
{


}


	    

