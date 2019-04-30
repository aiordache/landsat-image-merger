
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "gui.hpp"
#include "handler.hpp"
#include "image_frame.hpp"




////Event Table Start
BEGIN_EVENT_TABLE(MainFrame,wxFrame)
	EVT_CLOSE(MainFrame::OnClose)
	EVT_TEXT_ENTER(ID_FORMULATEXT,MainFrame::computeIndexClick)
	EVT_BUTTON(ID_COMPUTEINDEX,MainFrame::computeIndexClick)
	EVT_BUTTON(ID_NDVIBUTTON,MainFrame::ndviButtonClick)
	EVT_BUTTON(ID_BROWSE6BUTTON,MainFrame::Browse6ButtonClick)
	EVT_BUTTON(ID_WXBUTTON2,MainFrame::ndwiButtonClick)
	EVT_BUTTON(ID_BROWSE5BUTTON,MainFrame::Browse5ButtonClick)
	EVT_BUTTON(ID_BROWSE4BUTTON,MainFrame::Browse4ButtonClick)
	EVT_BUTTON(ID_SAVEBUTTON,MainFrame::SaveClick)
	EVT_BUTTON(ID_BROWSE3,MainFrame::Browse3Click)
	EVT_BUTTON(ID_BROWSE2BUTTON,MainFrame::Browse2Click)
	EVT_BUTTON(ID_BROWSE1BUTTON,MainFrame::Browse1Click)
	EVT_BUTTON(ID_TRANSFORMBUTTON,MainFrame::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
    SetTitle(wxT(title));
	SetSize(8,8,838,568);
    // set the frame icon
    SetIcon(icon_px);

	CreateGUIControls();
}

MainFrame::~MainFrame()
{
}

void MainFrame::CreateGUIControls()
{
	////GUI Items Creation Start

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(1, -9), wxSize(952, 619));

	TransformButton = new wxButton(WxPanel1, ID_TRANSFORMBUTTON, wxT("Create RGB  Image"), wxPoint(104, 312), wxSize(118, 30), 0, wxDefaultValidator, wxT("TransformButton"));

	Band3 = new wxTextCtrl(WxPanel1, ID_BAND3, wxT(""), wxPoint(77, 114), wxSize(288, 22), 0, wxDefaultValidator, wxT("Band3"));

	Band2 = new wxTextCtrl(WxPanel1, ID_BAND2, wxT(""), wxPoint(78, 73), wxSize(288, 22), 0, wxDefaultValidator, wxT("Band2"));

	Band1 = new wxTextCtrl(WxPanel1, ID_BAND1, wxT(""), wxPoint(78, 31), wxSize(288, 22), 0, wxDefaultValidator, wxT("Band1"));

	RComponent = new wxStaticText(WxPanel1, ID_RCOMPONENT, wxT("R"), wxPoint(32, 114), wxDefaultSize, 0, wxT("RComponent"));
	RComponent->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	GComponent = new wxStaticText(WxPanel1, ID_GCOMPONENT, wxT("G"), wxPoint(33, 72), wxDefaultSize, 0, wxT("GComponent"));
	GComponent->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	BComponent = new wxStaticText(WxPanel1, ID_BCOMPONENT, wxT("B"), wxPoint(35, 30), wxDefaultSize, 0, wxT("BComponent"));
	BComponent->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	Browse1Button = new wxButton(WxPanel1, ID_BROWSE1BUTTON, wxT("Browse"), wxPoint(374, 110), wxSize(49, 28), 0, wxDefaultValidator, wxT("Browse1Button"));

	Browse2Button = new wxButton(WxPanel1, ID_BROWSE2BUTTON, wxT("Browse"), wxPoint(376, 70), wxSize(49, 29), 0, wxDefaultValidator, wxT("Browse2Button"));

	Browse3Button = new wxButton(WxPanel1, ID_BROWSE3, wxT("Browse"), wxPoint(376, 23), wxSize(49, 29), 0, wxDefaultValidator, wxT("Browse3Button"));

	SaveButton = new wxButton(WxPanel1, ID_SAVEBUTTON, wxT("Save"), wxPoint(255, 312), wxSize(112, 30), 0, wxDefaultValidator, wxT("SaveButton"));

	WxStaticText1 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT1, wxT("NIR"), wxPoint(32, 162), wxDefaultSize, 0, wxT("WxStaticText1"));
	WxStaticText1->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	Band4 = new wxTextCtrl(WxPanel1, ID_BAND4, wxT(""), wxPoint(77, 163), wxSize(288, 22), 0, wxDefaultValidator, wxT("Band4"));

	Browse4Button = new wxButton(WxPanel1, ID_BROWSE4BUTTON, wxT("Browse"), wxPoint(376, 162), wxSize(49, 30), 0, wxDefaultValidator, wxT("Browse4Button"));

	WxStaticText2 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT2, wxT("MIR"), wxPoint(31, 210), wxDefaultSize, 0, wxT("WxStaticText2"));
	WxStaticText2->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	Band5 = new wxTextCtrl(WxPanel1, ID_BAND5, wxT(""), wxPoint(76, 210), wxSize(287, 22), 0, wxDefaultValidator, wxT("Band5"));

	Browse5Button = new wxButton(WxPanel1, ID_BROWSE5BUTTON, wxT("Browse"), wxPoint(377, 208), wxSize(49, 29), 0, wxDefaultValidator, wxT("Browse5Button"));

	WxButton2 = new wxButton(WxPanel1, ID_WXBUTTON2, wxT("Compute NDWI"), wxPoint(676, 269), wxSize(105, 29), 0, wxDefaultValidator, wxT("WxButton2"));

	WxStaticText3 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT3, wxT("ThIR"), wxPoint(30, 257), wxDefaultSize, 0, wxT("WxStaticText3"));
	WxStaticText3->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	Band6 = new wxTextCtrl(WxPanel1, ID_BAND6, wxT(""), wxPoint(77, 257), wxSize(288, 22), 0, wxDefaultValidator, wxT("Band6"));

	Browse6Button = new wxButton(WxPanel1, ID_BROWSE6BUTTON, wxT("Browse"), wxPoint(377, 255), wxSize(49, 28), 0, wxDefaultValidator, wxT("Browse6Button"));

	wxArrayString arrayStringFor_WxRadioBox1;
	arrayStringFor_WxRadioBox1.Add(wxT("Grayscale"));
	arrayStringFor_WxRadioBox1.Add(wxT("Palette"));
	WxRadioBox1 = new wxRadioBox(WxPanel1, ID_WXRADIOBOX1, wxT(" NDVI  "), wxPoint(464, 85), wxSize(156, 72), arrayStringFor_WxRadioBox1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, wxT("WxRadioBox1"));
	WxRadioBox1->SetSelection(0);

	ndviButton = new wxButton(WxPanel1, ID_NDVIBUTTON, wxT("Compute NDVI"), wxPoint(674, 110), wxSize(105, 28), 0, wxDefaultValidator, wxT("ndviButton"));

	wxArrayString arrayStringFor_WxRadioBox2;
	arrayStringFor_WxRadioBox2.Add(wxT("Grayscale"));
	arrayStringFor_WxRadioBox2.Add(wxT("Palette"));
	WxRadioBox2 = new wxRadioBox(WxPanel1, ID_WXRADIOBOX2, wxT(" NDWI  "), wxPoint(470, 246), wxSize(161, 72), arrayStringFor_WxRadioBox2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, wxT("WxRadioBox2"));
	WxRadioBox2->SetSelection(0);

	WxStaticText4 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT4, wxT(" B + G + R = "), wxPoint(3, 317), wxDefaultSize, 0, wxT("WxStaticText4"));
	WxStaticText4->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	computeIndex = new wxButton(WxPanel1, ID_COMPUTEINDEX, wxT("Compute Index"), wxPoint(685, 427), wxSize(110, 32), 0, wxDefaultValidator, wxT("computeIndex"));

	Formula = new wxStaticBox(WxPanel1, ID_FORMULA, wxT("   Define Index   "), wxPoint(414, 369), wxSize(241, 168));

	FormulaText = new wxTextCtrl(WxPanel1, ID_FORMULATEXT, wxT(""), wxPoint(451, 393), wxSize(170, 29), 0, wxDefaultValidator, wxT("FormulaText"));
	FormulaText->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Arial")));

	wxArrayString arrayStringFor_IndexRadioBox;
	arrayStringFor_IndexRadioBox.Add(wxT("Grayscale"));
	arrayStringFor_IndexRadioBox.Add(wxT("Palette"));
	IndexRadioBox = new wxRadioBox(WxPanel1, ID_INDEXRADIOBOX, wxT("     Index    "), wxPoint(451, 443), wxSize(167, 66), arrayStringFor_IndexRadioBox, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, wxT("IndexRadioBox"));
	IndexRadioBox->SetSelection(0);

	WxStaticText6 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT6, wxT("____________________________"), wxPoint(562, 37), wxDefaultSize, wxTRANSPARENT_WINDOW, wxT("WxStaticText6"));

	WxStaticText7 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT7, wxT("NDVI  ="), wxPoint(479, 37), wxDefaultSize, 0, wxT("WxStaticText7"));
	WxStaticText7->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	WxStaticText5 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT5, wxT("band4 - band3"), wxPoint(599, 23), wxDefaultSize, wxTRANSPARENT_WINDOW, wxT("WxStaticText5"));
	WxStaticText5->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	WxStaticText8 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT8, wxT("band4 + band3"), wxPoint(599, 55), wxDefaultSize, 0, wxT("WxStaticText8"));
	WxStaticText8->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	WxStaticText9 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT9, wxT("NDWI  ="), wxPoint(479, 194), wxDefaultSize, 0, wxT("WxStaticText9"));
	WxStaticText9->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	WxStaticText10 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT10, wxT("____________________________"), wxPoint(562, 189), wxDefaultSize, wxTRANSPARENT_WINDOW, wxT("WxStaticText10"));

	WxStaticText11 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT11, wxT("band4 - band5"), wxPoint(599, 174), wxDefaultSize, wxTRANSPARENT_WINDOW, wxT("WxStaticText11"));
	WxStaticText11->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	WxStaticText12 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT12, wxT("band4 + band5"), wxPoint(599, 207), wxDefaultSize, 0, wxT("WxStaticText12"));
	WxStaticText12->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	WxStaticText13 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT13, wxT("Example for parser:"), wxPoint(8, 378), wxDefaultSize, 0, wxT("WxStaticText13"));
	WxStaticText13->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	WxStaticLine1 = new wxStaticLine(WxPanel1, ID_WXSTATICLINE1, wxPoint(8, 351), wxSize(810, -1), wxLI_HORIZONTAL);

	WxStaticText14 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT14, wxT("(b4-b3)/(b4+b3)"), wxPoint(54, 434), wxDefaultSize, 0, wxT("WxStaticText14"));
	WxStaticText14->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Arial")));

	//SaveDialog =  new wxFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("*.*"), wxSAVE);

	//FileDialog =  new wxFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("*.*"), wxOPEN);

	DisplayString = new wxStaticText(WxPanel1, ID_DISPLAYSTRING, wxT("String"), wxPoint(250, 402), wxDefaultSize, 0, wxT("DisplayString"));
	DisplayString->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Arial")));


	////GUI Items Creation End
}

void MainFrame::OnClose(wxCloseEvent& event)
{
	Destroy();
}

ImageHandler* tr = new ImageHandler();
wxBitmap bmp;


/*
 * WxButton1Click0
 */
void MainFrame::Browse1Click(wxCommandEvent& event)
{
    if(FileDialog->ShowModal() == wxID_OK)
    {
        Band3->Clear();
        Band3->AppendText(FileDialog->GetPath());
    }
}

/*
 * WxButton2Click
 */
void MainFrame::Browse2Click(wxCommandEvent& event)
{
 if(FileDialog->ShowModal() == wxID_OK)
    {
       Band2->Clear();
       Band2->AppendText(FileDialog->GetPath());
    }
}

/*
 * WxButton3Click
 */
void MainFrame::Browse3Click(wxCommandEvent& event)
{
	 if(FileDialog->ShowModal() == wxID_OK)
    {
        Band1->Clear();
        Band1->AppendText(FileDialog->GetPath());
    }
}

/*
 * WxButton4Click
 */
void MainFrame::SaveClick(wxCommandEvent& event)
{
    if (SaveDialog->ShowModal() == wxID_OK)
        if ((bmp.IsNull() == false))
                bmp.SaveFile(SaveDialog->GetPath(), wxBITMAP_TYPE_TIF, NULL);
}

/*
 * Browse4ButtonClick
 */
void MainFrame::Browse4ButtonClick(wxCommandEvent& event)
{
	if(FileDialog->ShowModal() == wxID_OK)
    {
       Band4->Clear();
       Band4->AppendText(FileDialog->GetPath());
    }
}

/*
 * Browse5ButtonClick
 */
void MainFrame::Browse5ButtonClick(wxCommandEvent& event)
{
	if(FileDialog->ShowModal() == wxID_OK)
    {
       Band5->Clear();
       Band5->AppendText(FileDialog->GetPath());
    }
}

/*
 * Browse6ButtonClick
 */
void MainFrame::Browse6ButtonClick(wxCommandEvent& event)
{
	if(FileDialog->ShowModal() == wxID_OK)
    {
       Band6->Clear();
       Band6->AppendText(FileDialog->GetPath());
    }
}

/*
 * WxButton1Click
 */
void MainFrame::WxButton1Click(wxCommandEvent& event)
{
    if (Band3->GetValue() != "" && Band2->GetValue() != "" && Band1->GetValue()!= "")
    {
        ImageFrame* pic = new ImageFrame(wxT("RGB Image"));

        /*wxImage* r = cvLoadImage(Band3->GetValue(), 0);
        wxImage* g = cvLoadImage(Band2->GetValue(), 0);
        wxImage* b = cvLoadImage(Band1->GetValue(), 0);


        wxImage* Image = tr->GenerateImage(r, g, b);
        if(!cvSaveImage("temp.tif", Image)) printf("Could not save: %s\n","temp.tif");

        wxBitmap images(wxT("temp.tif"), wxBITMAP_TYPE_TIF);

        cvReleaseImage(&b);
        cvReleaseImage(&g);
        cvReleaseImage(&r);

        bmp = images;
        pic->SetPicture(images);*/
        pic->Show(true);
    }
}

/*
 * ndviButtonClick
 */
void MainFrame::ndviButtonClick(wxCommandEvent& event)
{
    if (Band3->GetValue() != "" && Band4->GetValue()!= "")
    {
       ImageFrame* pic = new ImageFrame(wxT("NDVI image"));

       /* wxImage* red = cvLoadImage(Band3->GetValue(), 0);
        wxImage* infrared = cvLoadImage(Band4->GetValue(), 0);


        wxImage* Image = 0;

        if (WxRadioBox1->GetSelection() == 1)
            Image = tr->ComputeColoredNDVI(red, infrared);
        else
            Image = tr->ComputeNDVI(red, infrared);

        if(!cvSaveImage("temp.tif", Image)) printf("Could not save: %s\n","temp.tif");

        wxBitmap images(wxT("temp.tif"), wxBITMAP_TYPE_TIF);

        bmp = images;

        cvReleaseImage(&red);
        cvReleaseImage(&infrared);

        pic->SetPicture(images);*/

        pic->Show(true);
    }
}

/*
 * ndwiButtonClick
 */
void MainFrame::ndwiButtonClick(wxCommandEvent& event)
{
    if (Band5->GetValue() != "" && Band4->GetValue()!= "")
    {
       ImageFrame* pic = new ImageFrame(wxT("NDVI image"));
        /*
        wxImage* infrared = cvLoadImage(Band4->GetValue(), 0);
        wxImage* mirinfrared = cvLoadImage(Band5->GetValue(), 0);

        wxImage* Image = 0;

        if (WxRadioBox2->GetSelection() == 1)
            Image = tr->ComputeColoredNDWI(infrared, mirinfrared);
        else
            Image = tr->ComputeNDWI(infrared, mirinfrared);

        if(!cvSaveImage("temp.tif", Image)) printf("Could not save: %s\n","temp.tif");

        wxBitmap images(wxT("temp.tif"), wxBITMAP_TYPE_TIF);

        bmp = images;

        cvReleaseImage(&infrared);
        cvReleaseImage(&mirinfrared);

        pic->SetPicture(images);*/
        pic->Show(true);
    }
}

/*
 * computeIndexClick
 */
void MainFrame::computeIndexClick(wxCommandEvent& event)
{
	wxString str = FormulaText->GetValue();

    str = toPostfix(str);

    //reverse to infix notation

    for(int i = 0; i < str.Len() / 2; i++)
    {
        wxChar c = str[i];
        str[i] = str[str.Len() - 1 - i];
        str[str.Len() - 1 - i] = c;
    }

    for(int i = 0; i < str.Len(); i++)
    {
        if(str[i] == 'b')
        {
         str[i] = str[i-1];
         str[i-1] = 'b';
        }
    }

    BuildImage(str);
}

void MainFrame::BuildImage(wxString str)
{
    wxImage*  list[7];

    unsigned char k = '0';//for counting the images from expression

    for(int j = 0; j < 7; j++)
        list[j] = 0;

    int band = 0;



    for(int i = 0; i < str.Len() - 1; i++)
    {
        if (str[i] =='b')
        {
            band = (int)str[i + 1] - '0';
           // str.Remove(i , 1);
            str[i + 1] = (char)k;

            for(int l = i; l < str.Len() - 1; l++)
                if ((int)str[l]- '0' == band && str[l] == 'b')
                {
                    str[l + 1] = (char)(k);
                    //str.Remove(l, 1);
                }
                /*
            switch(band)
            {
                    case 1:
                        {
                            list[k - '0'] = cvLoadImage(Band1->GetValue(), 0);
                            break;
                        }
                    case 2:
                        {
                            list[k - '0'] = cvLoadImage(Band2->GetValue(), 0);
                            break;
                        }
                    case 3:
                        {
                            list[k - '0'] = cvLoadImage(Band3->GetValue(), 0);
                            break;
                        }
                    case 4:
                        {
                            list[k - '0'] = cvLoadImage(Band4->GetValue(), 0);
                            break;
                        }
                    case 5:
                        {
                            list[k - '0'] = cvLoadImage(Band5->GetValue(), 0);
                            break;
                        }
                    case 6:
                        {
                            list[k - '0'] = cvLoadImage(Band6->GetValue(), 0);
                            break;
                        }
            }*/
            k++;
            band = 0;
        }
    }

    DisplayString->SetLabel(str);


    char expr[100];

    strcpy(expr, (const char*)str.mb_str(wxConvUTF8));
    /*
    wxImage* Image = 0;

    if (IndexRadioBox->GetSelection() == 1)
        Image = tr->ComputeColoredIndex(list, expr);
    else
        Image = tr->ComputeIndex(list, expr);


    if (Image != 0)
    {
         ImageFrame* pic = new ImageFrame(wxT("Index Image"));

        if(!cvSaveImage("temp.tif", Image)) printf("Could not save: %s\n","temp.tif");

        wxBitmap images(wxT("temp.tif"), wxBITMAP_TYPE_TIF);

        bmp = images;

        pic->SetPicture(images);
        pic->Show(true);
    }
    for(int  i = 0; i < 7; i++)
    {
        if (list[i]!=0)
                cvReleaseImage(&list[i]);
    }*/
}

wxString MainFrame::toPostfix(wxString str)
{
        if (str.Len() == 2 && str[0] == 'b')
            return str;

        if (((!str.Contains(wxT("b"))) && (!str.Contains(wxT("+"))) && (!str.Contains(wxT("-"))) && (!str.Contains(wxT("*"))) && (!str.Contains(wxT("/")))))
            return str;

        if(str[0] == '(')
        {
            int k = 0;
            int n = 0;
            while(str[k] != ')' && k < str.Len())
            {
                k++;
                if (str[k] == '(')
                    n++;

                if (str[k] == ')' && n > 0)
                {
                    n--;
                    k++;

                    int q = 0;
                    while(str[k] == ')')
                    {
                        n--;
                        k++;
                        q = 1;
                    }
                    if (q == 1)
                    {
                        k--;
                    }
                }
            }
            if (k == str.Len() - 1)
            {
                str.Remove(0,1);
                str.Remove(str.Len() - 1, 1);
            }
        }
        int i = 0;

        while(i < str.Len() && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/')
        {
            if (str[i] =='(')
            {
                int no = 0;
                while(str[i] != ')' && i < str.Len())
                {
                    i++;
                    if (str[i] == '(')
                        no++;
                    if (str[i] == ')' && no > 0)
                    {
                        no--;
                        i++;
                        int q = 0;
                        while(str[i] == ')')
                        {
                            no--;
                            i++;
                            q = 1;
                        }
                        if (q == 1)
                        {
                            i--;
                        }
                    }
                }
            }
            i++;
        }
        wxString str1 = wxT("");
        wxString str2 = wxT("");

        str1.append(str.SubString(0, i - 1));
        str2.append(str.SubString(i + 1, str.Len()));

        wxString str3 = wxT("");

        str3.append(str[i]);

        str3.append(toPostfix(str1));

        str3.append(toPostfix(str2));

        return str3;
}
