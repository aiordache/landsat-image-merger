
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "gui.hpp"
#include "handler.hpp"

enum
  {
    MENU_Exit = wxID_HIGHEST,
    MENU_Open,
    MENU_Remove,
    MENU_SaveAs,
    MENU_Clear
  };


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
 EVT_MENU(MENU_Open,    MainFrame::OnImageOpen)
 EVT_MENU(MENU_Remove,  MainFrame::OnImageRemove)
 EVT_MENU(MENU_SaveAs,  MainFrame::OnImageSaveAs)
 EVT_MENU(MENU_Exit,    MainFrame::OnExit)
 EVT_MENU(MENU_Clear,   MainFrame::OnClear)
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
    std::cout<<mf_size.GetWidth()<<"  -- "<<mf_size.GetHeight()<<std::endl;
  
    menubar = new wxToolBar(this, wxID_ANY);    
    menubar->AddTool(MENU_Exit, wxT("Exit application"), wxBitmap(wxT("resources/icons/exit.png"), wxBITMAP_TYPE_PNG));
    menubar->AddTool(MENU_SaveAs, wxT("Save"), wxBitmap(wxT("resources/icons/save.png"), wxBITMAP_TYPE_PNG));
    menubar-> AddSeparator();
    menubar->AddTool(MENU_Clear, wxT("Clear"), wxBitmap(wxT("resources/icons/clear.png"), wxBITMAP_TYPE_PNG));
    
    menubar->Realize();

    
    wxPanel* displaypanel = new wxPanel(this, wxID_ANY);
    ic = new ImageContainer(displaypanel, wxID_ANY);
    ic->SetImage(wxImage("resources/image.tif"));
    
    wxBoxSizer* displaysizer = new wxBoxSizer(wxVERTICAL);
    displaysizer->Add(ic, 1, wxEXPAND);
    displaypanel->SetSizerAndFit(displaysizer);

    wxBoxSizer *mainsizer = new wxBoxSizer(wxVERTICAL);
    mainsizer->Add(menubar, 0, wxEXPAND);
    mainsizer->Add(displaypanel, 1, wxEXPAND | wxALL, 10);
    
    SetSizer(mainsizer);

    
}
void MainFrame::OnClear( wxCommandEvent& event )
{
   std::cout<<"Clear Image..."<<std::endl;
   ic->SetImage(wxBitmap(wxT("resources/icons/logo.png"), wxBITMAP_TYPE_PNG).ConvertToImage());
    
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
