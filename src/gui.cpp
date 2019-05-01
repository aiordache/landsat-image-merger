
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "gui.hpp"
#include "handler.hpp"


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
 EVT_BUTTON(BUTTON_Clear, MainFrame::OnClear)
 EVT_BUTTON(MENU_Open,    MainFrame::OnImageOpen)
 EVT_BUTTON(MENU_Remove,  MainFrame::OnImageRemove)
 EVT_BUTTON(MENU_SaveAs,  MainFrame::OnImageSaveAs)
 EVT_BUTTON(MENU_Exit,    MainFrame::OnExit)
END_EVENT_TABLE()

  
MainFrame::MainFrame(wxWindow *parent, const wxString &title, wxWindowID id, const wxPoint &position, const wxSize& mf_size, long style)
: wxFrame(parent, id, title, position, mf_size, style)
{
  SetTitle(title);
  SetSize(mf_size);

  // set the frame icon
  SetIcon(icon_xpm_data);

  wxInitAllImageHandlers(); 


  CreateGUIControls(mf_size);
  Center();
  //Fit();
}

MainFrame::~MainFrame()
{


}

void MainFrame::CreateGUIControls(const wxSize& mf_size)
{
    // create a menu bar
    menuBar = new wxMenuBar();

    imageMenu = new wxMenu();
    imageMenu->Append(MENU_Open, _("Load Bands..."), wxT("Load Band images"));
    imageMenu->AppendSeparator();
    imageMenu->Append(MENU_SaveAs, _T("&Save"));

    exitMenu = new wxMenu();
    exitMenu->Append(MENU_Exit, _("E&xit\tAlt-X"), wxT("Quit this program"));
    
    menuBar->Append(imageMenu, _("&Images"));
    //menuBar->Append(aboutMenu, _("&Help"));
    menuBar->Append(exitMenu, _("&Exit"));

    SetMenuBar(menuBar);



    std::cout<<mf_size.GetWidth()<<"  -- "<<mf_size.GetHeight()<<std::endl;



    wxPanel* controlpanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0));


    wxStaticText* loadString   = new wxStaticText( controlpanel , wxID_ANY , "Test 1" ) ;

    wxPanel* displaypanel = new wxPanel(this, wxID_ANY);

    wxStaticText* infoString = new wxStaticText( displaypanel , wxID_ANY , "Display Image..." );
    
    
    wxButton* clearButton = new wxButton(displaypanel , BUTTON_Clear , "CLEAR");
    
    
    
    ic = new ImageContainer(displaypanel, wxID_ANY);
    ic->SetImage(wxImage("resources/image.tif"));
    //layout management with sizers
    wxBoxSizer* controlsizer = new wxBoxSizer(wxHORIZONTAL);
    controlsizer->Add(loadString, 1, wxALL | wxEXPAND | wxALIGN_CENTER, 5);



    wxBoxSizer* displaysizer = new wxBoxSizer(wxVERTICAL);
    displaysizer->Add(infoString, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
    displaysizer->Add(ic, 1, wxEXPAND);



    wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);

    mainsizer->Add(controlpanel, 0, wxALIGN_CENTER, 10);
    mainsizer->Add(displaypanel, 1, wxEXPAND | wxALL, 10);
    //mainsizer->Add(ic, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 10);



    controlpanel->SetSizerAndFit(controlsizer);
    displaypanel->SetSizerAndFit(displaysizer);

    this->SetSizerAndFit(mainsizer);
}
void MainFrame::OnClear( wxCommandEvent& event )
{

}
		
void MainFrame::OnImageOpen(wxCommandEvent& event)
{
   std::cout<<"Opening Image..."<<std::endl;
}
void MainFrame::OnImageSaveAs(wxCommandEvent& event)
{

   std::cout<<"Save Image..."<<std::endl;
}
void MainFrame::OnImageRemove(wxCommandEvent& event)
{
  
   std::cout<<"Remove Image..."<<std::endl;
}


void MainFrame::OnExit( wxCommandEvent& event )
{
  std::cout<<"Exiting..."<<std::endl;
  Close(TRUE);
  
}

wxString MainFrame::toPostfix(wxString str)
{
    return str;
}
