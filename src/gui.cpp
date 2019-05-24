#include <wx/event.h>
#include <wx/filedlg.h>
#include <dirent.h>
#include "xpm_icons.hpp"
#include "gui.hpp"
#include <vector>
#include <algorithm>

using namespace std;

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
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
 EVT_MENU(B9,   MainFrame::OnLoadImage)
 EVT_MENU(B10,   MainFrame::OnLoadImage)
 EVT_MENU(B11,   MainFrame::OnLoadImage)
 EVT_MENU(B12,   MainFrame::OnLoadImage)
 
 EVT_RADIOBUTTON(RADIO_RGB,     MainFrame::OnRadioStatusChange)
 EVT_RADIOBUTTON(RADIO_NDVI,    MainFrame::OnRadioStatusChange)
 EVT_RADIOBUTTON(RADIO_NDWI,    MainFrame::OnRadioStatusChange)
 EVT_RADIOBUTTON(RADIO_FORMULA, MainFrame::OnRadioStatusChange)

 EVT_RADIOBUTTON(RADIO_DEF_COL_PALETTE,    MainFrame::OnPaletteRadioStatusChange)
 EVT_RADIOBUTTON(RADIO_CUSTOM_COL_PALETTE, MainFrame::OnPaletteRadioStatusChange)
 
 EVT_COMBOBOX(COLOR_COUNTER, MainFrame::OnColorCounterChange)
 EVT_COMMAND(COLOR_PALETTE, COLOR_SELECTED, MainFrame::OnColorPaletteChange)
 
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
    Fit();
}

MainFrame::~MainFrame()
{


}

void MainFrame::CreateGUIControls(const wxSize& mf_size)
{
    //object manipulating image operations
    imghandler = new ImageHandler();
    
    cout<<mf_size.GetWidth()<<"  -- "<<mf_size.GetHeight()<<endl;
  
    menubar = new wxToolBar(this, wxID_ANY);
    menubar->AddTool(MENU_Exit, wxT("Exit application"), wxBitmap(exit_icon));
    menubar->AddTool(MENU_SaveAs, wxT("Save"), wxBitmap(save_icon));
    menubar->AddSeparator();
    menubar->AddSeparator();
    menubar->AddStretchableSpace();
    
    menubar->AddTool(IMAGE_DIR, wxT("Band dir"), wxBitmap(folder_icon));
    menubar->SetToolShortHelp(IMAGE_DIR, "Load images from directory");
    menubar->AddSeparator();
    

    // here add the landsat bands text and load buttons
    //family can be: wx.DECORATIVE, wx.DEFAULT,wx.MODERN, wx.ROMAN, wx.SCRIPT or wx.SWISS.
    //style can be: wx.NORMAL, wx.SLANT or wx.ITALIC.
    //weight can be: wx.NORMAL, wx.LIGHT, or wx.BOLD

    wxFont font = wxFont(8, wxDECORATIVE, wxITALIC, wxNORMAL); 
    wxSize textsize = wxSize(18, -1);
    wxStaticText* st = new wxStaticText(menubar, wxID_ANY, _("B1"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B1, wxT("Band 1 - coastal aerosol"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B1, "Band 1 - coastal aerosol");		
    
    
    st = new wxStaticText(menubar, wxID_ANY, _("B2"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B2, wxT("Band 2 - blue"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B2, "Band 2 - blue");		
    
    
    st = new wxStaticText(menubar, wxID_ANY, _("B3"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B3, wxT("Band 3 - green"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B3, "Band 3 - green");
    
    st = new wxStaticText(menubar, wxID_ANY, _("B4"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B4, wxT("Band 4 - red"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B4, "Band 4 - red");
    
    st = new wxStaticText(menubar, wxID_ANY, _("B5"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B5, wxT("Band 5 - NIR"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B5, "Band 5 - Near Infrared\n(NIR)");
    
    st = new wxStaticText(menubar, wxID_ANY, _("B6"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B6, wxT("Band 6 - SWIR 1"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B6, "Band 6 - short-wave\ninfrared (SWIR) 1");
    
    st = new wxStaticText(menubar, wxID_ANY, _("B7"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B7, wxT("Band 7 - SWIR 2"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B7, "Band 7 - short-wave\ninfrared (SWIR) 2");
    
    st = new wxStaticText(menubar, wxID_ANY, _("B8"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B8, wxT("Band 8 - Panchromatic"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B8, "Band 8 - panchromatic");
    
     st = new wxStaticText(menubar, wxID_ANY, _("B9"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B9, wxT("Band 9"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B9, "Band 9");
    
     st = new wxStaticText(menubar, wxID_ANY, _("B10"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B10, wxT("Band 10"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B10, "Band 10");
    
     st = new wxStaticText(menubar, wxID_ANY, _("B11"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B11, wxT("Band 11"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B11, "Band 11");
    
     st = new wxStaticText(menubar, wxID_ANY, _("B12"), wxDefaultPosition, textsize, wxALIGN_CENTRE );
    st->SetFont(font);
    menubar->AddControl(st);
    menubar->AddTool(B12, wxT("Band 12"), wxBitmap(add_image_icon));
    menubar->SetToolShortHelp(B12, "Band 12");
    
    
    
    
    menubar->AddStretchableSpace();
    menubar->AddSeparator();
    menubar->AddTool(MENU_Clear, wxT("Clear"), wxBitmap(bin_icon));

    menubar->Realize();

    // OPERATIONS TOOLBAR

    operationsbar = new wxToolBar(this, wxID_ANY);
    
    formula = new wxTextCtrl(operationsbar, FORMULA,
        "",wxDefaultPosition, wxSize(200, 30), wxTE_PROCESS_ENTER);
    formula->SetFont(wxFont(14, wxDECORATIVE, wxITALIC, wxNORMAL));
    formula->Disable();
    
    formula->Bind(wxEVT_CHAR, &MainFrame::OnFormulaKeyDown, this);
    
    
    
    operationsbar->AddControl(new wxRadioButton(operationsbar, RADIO_RGB, _T("RGB")));
    operationsbar->AddControl(new wxRadioButton(operationsbar, RADIO_NDVI, _T("NDVI")));
    operationsbar->AddControl(new wxRadioButton(operationsbar, RADIO_NDWI, _T("NDWI")));
    operationsbar->AddControl(new wxRadioButton(operationsbar, RADIO_FORMULA, _T("Band Combination")));
    operationsbar->AddControl(formula);
    operationsbar->AddStretchableSpace();    
    operationsbar->Realize();

    
    
    palettebar    = new wxToolBar(this, wxID_ANY);
    
    palettebar->AddStretchableSpace();
    palettebar->AddControl(new wxStaticBitmap(palettebar, GRADIENT_BITMAP, *(imghandler->GetColorPaletteImage())));
    palettebar->AddStretchableSpace();
    palettebar->AddControl(new wxRadioButton(palettebar, RADIO_DEF_COL_PALETTE, _T("Default Color Scheme")));
    palettebar->AddStretchableSpace();
    palettebar->AddControl(new wxRadioButton(palettebar, RADIO_CUSTOM_COL_PALETTE, _T("Custom Color Scheme")));
    palettebar->AddStretchableSpace();
    

  
    colorpalette = new ColorPalette(palettebar, COLOR_PALETTE, "Color Palette");
    colorpalette->SetColorCount(3);
    colorpalette->Disable();
    palettebar->AddControl(colorpalette); 
    
    wxArrayString choices;
    choices.Add(wxT("2"));
    choices.Add(wxT("3"));
    choices.Add(wxT("4"));
    choices.Add(wxT("5"));
    choices.Add(wxT("6"));
    choices.Add(wxT("7"));
    choices.Add(wxT("8"));
    choices.Add(wxT("9"));
    choices.Add(wxT("10"));
    wxComboBox *cb = new wxComboBox(palettebar, COLOR_COUNTER, _T("3"), wxDefaultPosition, wxSize(60,20),choices, wxCB_READONLY);
    cb->Disable();
    palettebar->AddControl(cb);
    
    palettebar->AddStretchableSpace();
    palettebar->Realize();
    
    wxPanel* displaypanel = new wxPanel(this, wxID_ANY);
    ic = new ImageContainer(displaypanel, wxID_ANY);
    ic->SetImage(new wxImage("resources/image.tif"));
    
    
    wxBoxSizer* displaysizer = new wxBoxSizer(wxVERTICAL);
    displaysizer->Add(ic, 1, wxEXPAND);
    displaypanel->SetSizerAndFit(displaysizer);

    wxBoxSizer *mainsizer = new wxBoxSizer(wxVERTICAL);
    mainsizer->Add(menubar, 0, wxEXPAND);
    mainsizer->Add(palettebar, 0, wxEXPAND | wxLEFT);
    mainsizer->Add(operationsbar, 0, wxEXPAND | wxLEFT);
    
    mainsizer->Add(displaypanel, 1, wxEXPAND | wxALL, 10);
    
    SetSizer(mainsizer);
    
}


void MainFrame::UpdateImage()
{
   SetTitle("Updating image ....");
   
   wxImage* img = NULL;
   if (((wxRadioButton*)operationsbar->FindControl(RADIO_RGB))->GetValue())
        img = imghandler->GetRGBImage();
   else
   if (((wxRadioButton*)operationsbar->FindControl(RADIO_NDVI))->GetValue())
        img = imghandler->ComputeNDVI();
   else
   if (((wxRadioButton*)operationsbar->FindControl(RADIO_NDWI))->GetValue())
        img = imghandler->ComputeNDWI();
    else
    if (((wxRadioButton*)operationsbar->FindControl(RADIO_FORMULA))->GetValue())
    { 
        string s = (string)formula->GetLineText(0).c_str();
        img = imghandler->ComputeCustomIndex(s);
    }    
   
   if (img != NULL)
    {
        ic->SetImage(img);
        SetTitle("");
    }
    else
        SetTitle("Failed to generate image.");
}



void MainFrame::UpdateColorPalette()
{
    SetTitle("Updating Palette");

    if (((wxRadioButton*)palettebar->FindControl(RADIO_CUSTOM_COL_PALETTE))->GetValue())
    {
        vector<unsigned int> colors = colorpalette->GetColorList();
        // load custom color scheme 
        imghandler->LoadColorPalette(colors);
    }
    wxStaticBitmap* bitmap = (wxStaticBitmap*)palettebar->FindControl(GRADIENT_BITMAP);

    bitmap->SetBitmap(*(imghandler->GetColorPaletteImage()));

    SetTitle("Color Palette Updated. Apply to image...");
    
    UpdateImage();
}


 
// EVENT HANDLERS
void MainFrame::OnLoadFromDir( wxCommandEvent& event )
{
    SetTitle("");
    wxDirDialog dlg(NULL, "Choose input directory", "",
                wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if ( dlg.ShowModal() == wxID_OK )
    {
        wxString path = dlg.GetPath();
        //list opened directory
        DIR* dirp = opendir(path.c_str());
        struct dirent * ent;
        wxString extension[] = {".jpg", ".tif",".png",".jpeg", ".tiff"};
        
        vector<string> filenames;

        while ((ent = readdir(dirp)) != NULL) {
            wxString s = ent->d_name;
            for(int i=0;i<5; i++)
                if (s.Lower().EndsWith(extension[i]))
                    filenames.push_back((string)path.c_str() + "/" +(string)s.c_str());
        }
        closedir(dirp);
        //discard previous images if any
        OnDiscardAllImages(event);

        //sort filenames
        std::sort(filenames.begin(), filenames.end());
        for (int i = 0; i < filenames.size(); ++i)
            if (i <= B8 - B1)
            {
                imghandler->AddImagePath(filenames[i]);
                menubar->SetToolNormalBitmap(B1+i, wxBitmap(color_image_icon));
            }
        
        UpdateImage();
    }

}

void MainFrame::OnLoadImage( wxCommandEvent& event )
{
   SetTitle("");
   int id = event.GetId();
   //load image file
   wxFileDialog dlg(
		this, _("Open Image _?"), wxEmptyString, wxEmptyString,
		_("Image files|*.tif;*.tiff;*.TIF;*.TIFF;*.png;*.PNG;*.jpeg;*.jpg;*.JPG;*.JPEG|TIF Files (*.tif;*.tiff)|*.tif;*.tiff;*.TIF;*.TIFF|PNG files (*.png)|*.png;*.PNG|JPEG Files (*.jpeg;*.jpg)|*.jpeg;*.jpg;*.JPG;*.JPEG"),
		wxFD_DEFAULT_STYLE | wxFD_FILE_MUST_EXIST, wxDefaultPosition);

	if (dlg.ShowModal() == wxID_OK) // If the user clicked "OK"
	{
		imghandler->SetImagePath((string)dlg.GetPath().c_str(), id - B1);
		SetTitle(wxString("Loaded image - ") << dlg.GetFilename());
		// set button image
        menubar->SetToolNormalBitmap(id, wxBitmap(color_image_icon));
	}
}

void MainFrame::OnDiscardAllImages( wxCommandEvent& event )
{
    SetTitle("");
    //change icons in menubar
    for(int id = B1; id <= B8; id++)
        menubar->SetToolNormalBitmap(id, wxBitmap(add_image_icon));
     
    imghandler->ResetImagePaths();
}

void MainFrame::OnImageSaveAs(wxCommandEvent& event)
{
    SetTitle("");
    wxFileDialog dlg(
	    this, _("Save File As _?"), wxEmptyString, wxEmptyString,
	    _("Image files|*.tif;*.tiff;*.TIF;*.TIFF;*.png;*.PNG;*.jpeg;*.jpg;*.JPG;*.JPEG|TIF Files (*.tif;*.tiff)|*.tif;*.tiff;*.TIF;*.TIFF|PNG files (*.png)|*.png;*.PNG|JPEG Files (*.jpeg;*.jpg)|*.jpeg;*.jpg;*.JPG;*.JPEG"),
	    wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

    if (dlg.ShowModal() == wxID_OK)
    {
        
        imghandler->GetImage()->SaveFile((string)dlg.GetPath(), wxBITMAP_TYPE_JPEG);
	    //imghandler->SaveImage((string)dlg.GetPath());
	    SetTitle(wxString("Saved image to - ") << dlg.GetFilename());
    }
}

void MainFrame::OnExit( wxCommandEvent& event )
{
    SetTitle("Exiting...");
    Close(TRUE);
}

void MainFrame::OnRadioStatusChange(wxCommandEvent& event)
{
    SetTitle("");
    if (((wxRadioButton*)operationsbar->FindControl(RADIO_FORMULA))->GetValue())
    {
        formula->Enable();
        return;
    }
    else
        formula->Disable();
    UpdateImage();
}


void MainFrame::OnPaletteRadioStatusChange(wxCommandEvent& event)
{
    SetTitle("");
    if (((wxRadioButton*)palettebar->FindControl(RADIO_DEF_COL_PALETTE))->GetValue())
    {
        colorpalette->Disable();
        ((wxComboBox*)palettebar->FindControl(COLOR_COUNTER))->Disable();
        imghandler->ResetColorPalette();
    }
    else
    {
        colorpalette->Enable();
        ((wxComboBox*)palettebar->FindControl(COLOR_COUNTER))->Enable();
    }
    UpdateColorPalette();
}

void MainFrame::OnColorPaletteChange(wxCommandEvent& event)
{
    UpdateColorPalette();
}
void MainFrame::OnColorCounterChange(wxCommandEvent& event)
{ 
    wxComboBox*cb = (wxComboBox*)palettebar->FindControl(COLOR_COUNTER);
        
    int num = wxAtoi(cb->GetStringSelection());
    
    colorpalette->SetColorCount( num);
}

void MainFrame::OnFormulaKeyDown(wxKeyEvent& event)
{
    int key = event.GetKeyCode();
    if (key == WXK_BACK || key == WXK_LEFT || key == WXK_RIGHT)
    {
        event.Skip();
        return;
    }
       
    if(key == WXK_RETURN)
    {   
        event.Skip();
        UpdateImage();
        return;
    }
    
    char c = event.GetUnicodeKey();
    const string allowedchars = "bB0123456789+-*/()";
    
    if (int(allowedchars.find(c)) != -1)
        event.Skip();

}

