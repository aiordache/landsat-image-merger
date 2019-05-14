

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
 

enum
  {
    MENU_Exit = wxID_HIGHEST,
    MENU_Remove,
    MENU_SaveAs,
    MENU_Clear,
    IMAGE_DIR,
    B1,B2,B3,B4,B5,B6,B7,B8,
    GENERATE_BUTTON,
    RADIO_RGB,
    RADIO_NDVI,
    RADIO_FORMULA
  };
 
 
class MainFrame : public wxFrame
{
	private:
	    
        ImageHandler    *imghandler;
        
        wxToolBar       *menubar;
        wxToolBar       *operationsbar;
        wxTextCtrl      *formula;
        ImageContainer  *ic;
        
        void OnLoadFromDir(wxCommandEvent& event);
        void OnLoadImage(wxCommandEvent& event);
        
        void OnImageSaveAs(wxCommandEvent& event);
        void OnImageRemove(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event );
        void OnDiscardAllImages(wxCommandEvent& event );

	    void OnGenerateImage(wxCommandEvent& event);
        void OnRadioStatusChange(wxCommandEvent& event);
        void CreateGUIControls(const wxSize& mf_size);


        DECLARE_EVENT_TABLE();

	public:
		MainFrame(wxWindow *parent, const wxString &title = wxT("Satellite Image Processing Project"), wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& mf_size = wxSize(1200, 800), const long style = wxDEFAULT_FRAME_STYLE);
		~MainFrame();

};




