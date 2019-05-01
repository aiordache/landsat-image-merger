

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

#include <wx/filedlg.h>
#include <wx/statline.h>
#include <wx/statbox.h>
#include <wx/radiobox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/panel.h>

static const char *icon_xpm_data[] = {
/* columns rows colors chars-per-pixel */
"32 32 6 1",
"  c black",
". c navy",
"X c red",
"o c yellow",
"O c gray100",
"+ c None",
/* pixels */
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++              ++++++++++",
"++++++++ ............ ++++++++++",
"++++++++ ............ ++++++++++",
"++++++++ .OO......... ++++++++++",
"++++++++ .OO......... ++++++++++",
"++++++++ .OO......... ++++++++++",
"++++++++ .OO......              ",
"++++++++ .OO...... oooooooooooo ",
"         .OO...... oooooooooooo ",
" XXXXXXX .OO...... oOOooooooooo ",
" XXXXXXX .OO...... oOOooooooooo ",
" XOOXXXX ......... oOOooooooooo ",
" XOOXXXX ......... oOOooooooooo ",
" XOOXXXX           oOOooooooooo ",
" XOOXXXXXXXXX ++++ oOOooooooooo ",
" XOOXXXXXXXXX ++++ oOOooooooooo ",
" XOOXXXXXXXXX ++++ oOOooooooooo ",
" XOOXXXXXXXXX ++++ oooooooooooo ",
" XOOXXXXXXXXX ++++ oooooooooooo ",
" XXXXXXXXXXXX ++++              ",
" XXXXXXXXXXXX ++++++++++++++++++",
"              ++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++"
};

enum
  {
    BUTTON_Clear = wxID_HIGHEST + 1,
    MENU_Open,
    MENU_Remove,
    MENU_SaveAs,
    MENU_Exit
  };


 
class MainFrame : public wxFrame
{
	private:
	
	  wxMenuBar *menuBar;
		wxMenu    *imageMenu;
		wxMenu    *aboutMenu;
		wxMenu    *exitMenu;
		
		ImageContainer* ic;
		
		void OpenImage(wxCommandEvent& event);
    void SaveImage(wxCommandEvent& event);
    void RemoveImage(wxCommandEvent& event);
    void OnExit( wxCommandEvent& event );
    void OnClear( wxCommandEvent& event );
		
		void CreateGUIControls(const wxSize& mf_size);

    
		DECLARE_EVENT_TABLE();

	public:
		MainFrame(wxWindow *parent, const wxString &title = wxT("Satellite Image Processing Project"), wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& mf_size = wxSize(800, 600), const long style = wxDEFAULT_FRAME_STYLE);

    
  
		wxString toPostfix(wxString str);

		~MainFrame();

};
