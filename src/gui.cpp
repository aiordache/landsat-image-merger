
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "xpm_icons.hpp"
#include "gui.hpp"
#include "handler.hpp"


enum
  {
    MENU_Exit = wxID_HIGHEST,
    MENU_Remove,
    MENU_SaveAs,
    MENU_Clear,
    IMAGE_DIR,
    B1,B2,B3,B4,B5,B6,B7,B8
  };


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
 EVT_MENU(MENU_Remove,  MainFrame::OnImageRemove)
 EVT_MENU(MENU_SaveAs,  MainFrame::OnImageSaveAs)
 EVT_MENU(MENU_Exit,    MainFrame::OnExit)
 EVT_MENU(MENU_Clear,   MainFrame::OnDiscardAllImages)
 
 EVT_MENU(IMAGE_DIR,   MainFrame::OnLoadFromDir)
 EVT_MENU(B1,   MainFrame::OnLoadImage)
 EVT_MENU(B2,   MainFrame::OnLoadImage)
 EVT_MENU(B3,   MainFrame::OnLoadImage)
 EVT_MENU(B4,   MainFrame::OnLoadImage)
 EVT_MENU(B5,   MainFrame::OnLoadImage)
 EVT_MENU(B6,   MainFrame::OnLoadImage)
 EVT_MENU(B7,   MainFrame::OnLoadImage)
 EVT_MENU(B8,   MainFrame::OnLoadImage)
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
    menubar->AddTool(MENU_Exit, wxT("Exit application"), wxBitmap(exit_icon));
    menubar->AddTool(MENU_SaveAs, wxT("Save"), wxBitmap(save_icon));
    menubar->AddSeparator();
    menubar->AddSeparator();
    menubar->AddStretchableSpace();
    
    menubar->AddTool(IMAGE_DIR, wxT("Band dir"), wxBitmap(empty_folder_icon));
    
    //menubar->AddTool(MENU_Open, wxT("Band 1"), wxBitmap(folder_icon));
    menubar->AddSeparator();
    // here add the landsat bands load buttons
    menubar->AddTool(B1, wxT("Band 1"), wxBitmap(add_image_icon));
    menubar->AddTool(B2, wxT("Band 2"), wxBitmap(add_image_icon));
    menubar->AddTool(B3, wxT("Band 3"), wxBitmap(add_image_icon));
    menubar->AddTool(B4, wxT("Band 4"), wxBitmap(add_image_icon));
    menubar->AddTool(B5, wxT("Band 5"), wxBitmap(add_image_icon));
    menubar->AddTool(B6, wxT("Band 6"), wxBitmap(add_image_icon));
    menubar->AddTool(B7, wxT("Band 7"), wxBitmap(add_image_icon));
    menubar->AddTool(B8, wxT("Band 8"), wxBitmap(add_image_icon));
    
    
    
    menubar->AddSeparator();
    
    menubar->AddStretchableSpace();
    menubar->AddSeparator();
    menubar->AddSeparator();
    menubar->AddTool(MENU_Clear, wxT("Clear"), wxBitmap(bin_icon));
 
    
    
    
    
    //ImageLoader* il = new ImageLoader(this, BANDS, 7);
    
    //menubar->AddTool(li);
    
    menubar->Realize();

    
    wxPanel* displaypanel = new wxPanel(this, wxID_ANY);
    ic = new ImageContainer(displaypanel, wxID_ANY);
    ic->SetImage(wxImage("resources/image.tif"));
    
    wxBoxSizer* displaysizer = new wxBoxSizer(wxVERTICAL);
    displaysizer->Add(ic, 1, wxEXPAND);
    displaypanel->SetSizerAndFit(displaysizer);

    wxBoxSizer *mainsizer = new wxBoxSizer(wxVERTICAL);
    mainsizer->Add(menubar, 0, wxEXPAND);
    //mainsizer->Add(il, 0, wxEXPAND);
    
    mainsizer->Add(displaypanel, 1, wxEXPAND | wxALL, 10);
    
    SetSizer(mainsizer);

    
}

void MainFrame::OnLoadFromDir( wxCommandEvent& event )
{
   std::cout<<"Clear Image..."<<std::endl;
   ic->SetImage(wxBitmap(wxT("resources/icons/logo.png"), wxBITMAP_TYPE_PNG).ConvertToImage());
    
}

void MainFrame::OnLoadImage( wxCommandEvent& event )
{
   std::cout<<"Load Images from dir..."<<std::endl;
   ic->SetImage(wxBitmap(wxT("resources/icons/logo.png"), wxBITMAP_TYPE_PNG).ConvertToImage());
    
}

void MainFrame::OnDiscardAllImages( wxCommandEvent& event )
{
   std::cout<<"Discard All Image..."<<std::endl;
   ic->SetImage(wxBitmap(wxT("resources/icons/logo.png"), wxBITMAP_TYPE_PNG).ConvertToImage());
    
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
