
#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif
#include "wx/control.h"
#include <vector>

class ColorPalette: public wxControl
{
    private:
        std::vector<unsigned int>   pickedcolors = {};
        wxBitmap                    *bitmap;
        
        void    CreatePaletteBitmap();
    public:
        DECLARE_DYNAMIC_CLASS(ColorPalette);

	    ColorPalette (){};
	    ColorPalette (wxWindow* parent, wxWindowID id, const wxString& txt);
	    void    SetColorCount(int num);
	    void    SetColor(int index, unsigned int color);
	    void OnPaint(wxPaintEvent& event);

	    DECLARE_EVENT_TABLE();
	   
};


