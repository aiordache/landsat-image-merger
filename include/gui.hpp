

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif
#include <wx/textctrl.h>
#include <wx/button.h>
#include "image_container.hpp"
#include "image_handler.hpp"
#include "color_palette.hpp"

enum
  {
    MENU_Exit = wxID_HIGHEST,
    MENU_Remove,
    MENU_SaveAs,
    MENU_Clear,
    IMAGE_DIR,
    B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,
    RADIO_RGB,
    RADIO_NDVI,
    RADIO_NDWI,
    RADIO_FORMULA,
    RADIO_DEF_COL_PALETTE,
    RADIO_CUSTOM_COL_PALETTE,
    GRADIENT_BITMAP,
    COLOR_COUNTER,
    COLOR_PALETTE,
    FORMULA
  };
 
 
class MainFrame : public wxFrame
{
	public:
		MainFrame(wxWindow *parent, const wxString &title = wxT("Satellite Image Processing Project"), wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& mf_size = wxSize(1200, 800), const long style = wxDEFAULT_FRAME_STYLE);
		~MainFrame();
    
    private:
	    
        ImageHandler    *imghandler;
        
        wxToolBar       *menubar;
        wxToolBar       *operationsbar;
        wxToolBar       *palettebar;
        wxTextCtrl      *formula;
        ColorPalette    *colorpalette;    
        ImageContainer  *ic;
        
        void UpdateImage();
        void UpdateColorPalette();
        
        // EVENT HANDLERS
        void OnLoadFromDir(wxCommandEvent& event);
        void OnLoadImage(wxCommandEvent& event);
        
        void OnImageSaveAs(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event );
        void OnDiscardAllImages(wxCommandEvent& event );

        void OnRadioStatusChange(wxCommandEvent& event);
        void OnPaletteRadioStatusChange(wxCommandEvent& event);
        void OnColorPaletteChange(wxCommandEvent& event);
        void OnColorCounterChange(wxCommandEvent& event);
        
        void OnFormulaEnter(wxCommandEvent& event);
        void OnFormulaKeyDown(wxKeyEvent& event);
        void CreateGUIControls(const wxSize& mf_size);

        DECLARE_EVENT_TABLE();
};




