
#include "image_container.hpp"

ImageContainer::ImageContainer(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id,  wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    SetSize(wxSize(width, height));
    SetMinSize(wxSize(width, height));

    SetScrollbars(1,1, width, height, 0, 0);
    SetScrollRate(5, 5);

    Bind(wxEVT_SIZE, &ImageContainer::OnSize, this);
    Bind(wxEVT_MOUSEWHEEL, &ImageContainer::OnMouse, this);
};

ImageContainer::~ImageContainer()
{
};

void ImageContainer::SetImage(wxImage* img)
{
    image = img;
    zoom = 10;
    GetClientSize(&width, &height);
    FitToCanvas();
};

void ImageContainer::Clear()
{
    image = NULL;
    Refresh();
};

void ImageContainer::SetMessage(wxString* msg)
{
    message = msg;
}

void ImageContainer::FitToCanvas()
{
    if (image == NULL) return;
    
    int w = image->GetWidth();
    int h = image->GetHeight();

    if (zoom < 10)
    {
        w = (double)w * (double)(10 - zoom)/ 10.0 ;
        h = (double)h * (double)(10 - zoom)/ 10.0 ;
    }

    double xratio = (double) width / (double) w;
    double yratio = (double) height / (double) h;
    double ratio = xratio < yratio ? xratio : yratio;
    int new_width = (int)(ratio * (double)w);
    int new_height = (int)(ratio * (double)h);
    
    if (zoom == 10 || w <= width || h <= height)
        rect = wxRect(std::abs(width - new_width)/2,std::abs(height - new_height)/2, new_width, new_height);
    else 
        rect = wxRect(0, 0 , w, h);
        
    SetScrollbars(1, 1, rect.width, rect.height, std::abs(rect.width - width)/2, std::abs(rect.height - height)/2);
        
    Refresh();
};


// EVENTS
void ImageContainer::OnDraw(wxDC& dc)
{
    //fills canvas with black
    dc.SetBackground( *wxBLACK_BRUSH );
    dc.Clear();

    // draw bitmap - centered
    if (image != NULL)
        dc.DrawBitmap(image->Scale(rect.width, rect.height, wxIMAGE_QUALITY_HIGH), rect.x, rect.y, false);
    else if (message != NULL)
    {
        wxFont font(16, wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD);
        dc.SetFont(font);
        dc.SetTextForeground(*wxWHITE);
        dc.DrawText(*message, (width - (message->length()* 16))/2, 30); 
    }
};

void ImageContainer::OnSize(wxSizeEvent& event)
{
    GetClientSize(&width, &height);
    FitToCanvas();
};

void ImageContainer::OnMouse(wxMouseEvent &event)
{
    if (event.GetWheelRotation() != 0)
    {
        int old_zoom = zoom;
        zoom = ((event.GetWheelRotation() > 0)? -1 : +1) + zoom; 
        zoom = (zoom > 10) ? 10 : (zoom < 1) ? 1 : zoom;
        if (old_zoom == zoom)
            return;
        
        FitToCanvas();
        
    }
};

