

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

#include <wx/filedlg.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/panel.h>
#include "image_container.hpp"

 
class MainFrame : public wxFrame
{
	private:
        wxToolBar       *menubar;
        ImageContainer  *ic;
        //Landsat Bands
        wxImage*         BANDS[7];
        
        
        void OnLoadFromDir(wxCommandEvent& event);
        void OnLoadImage(wxCommandEvent& event);
        
        void OnImageSaveAs(wxCommandEvent& event);
        void OnImageRemove(wxCommandEvent& event);
        void OnExit( wxCommandEvent& event );
        void OnDiscardAllImages( wxCommandEvent& event );

        void CreateGUIControls(const wxSize& mf_size);


        DECLARE_EVENT_TABLE();

	public:
		MainFrame(wxWindow *parent, const wxString &title = wxT("Satellite Image Processing Project"), wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& mf_size = wxSize(1200, 800), const long style = wxDEFAULT_FRAME_STYLE);

    
  
		wxString toPostfix(wxString str);

		~MainFrame();

};




