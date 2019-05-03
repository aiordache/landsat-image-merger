
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
    
    
    // here add the landsat bands text and load buttons
    //family can be: wx.DECORATIVE, wx.DEFAULT,wx.MODERN, wx.ROMAN, wx.SCRIPT or wx.SWISS.
    //style can be: wx.NORMAL, wx.SLANT or wx.ITALIC.
    //weight can be: wx.NORMAL, wx.LIGHT, or wx.BOLD

    wxFont font = wxFont(8, wxDECORATIVE, wxITALIC, wxNORMAL); 
    wxSize textsize = wxSize(18, -1);
    wxStaticText* st = new wxStaticText(menubar, wxID_ANY, _("Blue"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B1, wxT("Visible Blue"), wxBitmap(add_image_icon));
    
    st = new wxStaticText(menubar, wxID_ANY, _("Green"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B2, wxT("Visible Green"), wxBitmap(add_image_icon));
    
    
    st = new wxStaticText(menubar, wxID_ANY, _("Red"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B3, wxT("Visible Red"), wxBitmap(add_image_icon));
    
    st = new wxStaticText(menubar, wxID_ANY, _("Near\n Infr"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B4, wxT("Near Infrared"), wxBitmap(add_image_icon));
    
    st = new wxStaticText(menubar, wxID_ANY, _("Mid\nInfr"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B5, wxT("Middle Infrared"), wxBitmap(add_image_icon));
    
    st = new wxStaticText(menubar, wxID_ANY, _("Therm\nInfr"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B6, wxT("Thermal Infrared"), wxBitmap(add_image_icon));
    
    st = new wxStaticText(menubar, wxID_ANY, _("Mid\nInfr"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B7, wxT("Middle Infrared"), wxBitmap(add_image_icon));
    
    st = new wxStaticText(menubar, wxID_ANY, _("Panch-\nromatic"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B8, wxT("Panchromatic"), wxBitmap(add_image_icon));
    
    
    menubar->AddStretchableSpace();
    menubar->AddSeparator();
    menubar->AddTool(MENU_Clear, wxT("Clear"), wxBitmap(bin_icon));
 
    menubar->SetToolShortHelp(B1,"Test");
    std::cout<<B1<<"   "<<menubar->GetToolsCount()<<"  \n";
    
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
   //ic->SetImage(wxBitmap(wxT("resources/icons/logo.png"), wxBITMAP_TYPE_PNG).ConvertToImage());
   for(int i =0; i < N; i++)
        if (BANDS[i] != NULL) 
        {
            free(BANDS[i]);
            BANDS[i] = NULL;
        }
    
    //reset toolbar
     
    
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
