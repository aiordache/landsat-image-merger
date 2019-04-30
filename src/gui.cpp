
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "gui.hpp"
#include "handler.hpp"
#include "image_container.hpp"


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
    /*menuBar = new wxMenuBar();

    imageMenu = new wxMenu();
    //imageMenu->Append(wxID_LOAD, _("Load Bands..."), wxT("Load Band images"));
    imageMenu->AppendSeparator();
    //imageMenu->Append(wxID_SAVE, _T("&Save"));
    //imageFile->Append(wxID_EXIT, _("E&xit\tAlt-X"), wxT("Quit this program"));

    aboutMenu = new wxMenu();
    aboutMenu->Append(wxID_ABOUT, _("&About...\tF1"), wxT("Show about dialog"));

    exitMenu = new wxMenu();

    menuBar->Append(imageMenu, _("&Images"));
    menuBar->Append(aboutMenu, _("&Help"));
    menuBar->Append(exitMenu, _("&Exit"));

    SetMenuBar(menuBar);
*/



    std::cout<<mf_size.GetWidth()<<"  -- "<<mf_size.GetHeight()<<std::endl;



    wxPanel* controlpanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0));


    wxStaticText* m_helloString   = new wxStaticText( controlpanel , wxID_ANY , "Test 1" ) ;
    wxStaticText* m_todayString   = new wxStaticText( controlpanel , wxID_ANY , "Test 2"  ) ;
    wxStaticText* m_thousandString = new wxStaticText( controlpanel , wxID_ANY , "Test 3" );

    wxPanel* displaypanel = new wxPanel(this, wxID_ANY);

    wxStaticText* infoString = new wxStaticText( displaypanel , wxID_ANY , "Display Image..." );
    ImageContainer* ic = new ImageContainer(displaypanel, wxID_ANY);//, wxBitmap(this->GetIcon()));
    //, wxSize(mf_size.GetWidth(), mf_size.GetHeight() * 0.5));//"resources/landsat_ro/LC08_L1TP_182029_20181030_20181030_01_RT_B11.TIF");

    //ic->SetImage(wxImage(icon_xpm_data));
    ic->SetImage(wxImage("resources/image.tif"));
    //layout management with sizers
    wxBoxSizer* controlsizer = new wxBoxSizer(wxHORIZONTAL);
    controlsizer->Add(m_helloString, 1, wxALL | wxEXPAND | wxALIGN_CENTER, 5);
    controlsizer->Add(m_todayString, 1, wxALL | wxEXPAND | wxALIGN_CENTER, 5);
    controlsizer->Add(m_thousandString, 1, wxALL | wxEXPAND | wxALIGN_CENTER, 5);



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


void MainFrame::OnClose(wxCloseEvent& event)
{
	Destroy();
}

wxString MainFrame::toPostfix(wxString str)
{
    return str;
}
