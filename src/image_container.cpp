
#include "image_container.hpp"

ImageContainer::ImageContainer(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id,  wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    SetSize(wxSize(width, height));
    SetMinSize(wxSize(width, height));

    SetScrollbars(1,1, rect.width, rect.height, 0, 0);
    SetScrollRate(5, 5);

    Bind(wxEVT_SIZE, &ImageContainer::OnSize, this);
    Bind(wxEVT_MOUSEWHEEL, &ImageContainer::OnMouse, this);

};

ImageContainer::~ImageContainer()
{
    delete image;
};

void ImageContainer::SetImage(wxImage img)
{
    
    delete image; image = NULL;
    image = new wxImage(img);
    rect = wxRect(0, 0 , image->GetWidth(), image->GetHeight());
    FitToCanvas();

};


void ImageContainer::FitToCanvas()
{
    if (zoom > maxzoomout)
        return;
    // get targeted area from the image
    int imgwidth = image->GetWidth();//rect.width;
    int imgheight = image->GetHeight();//   rect.height;

    double xratio = (double) width / (double) imgwidth;
    double yratio = (double) height / (double) imgheight;
    double ratio = xratio < yratio ? xratio : yratio;
    int new_width = (int)(ratio * imgwidth);
    int new_height = (int)(ratio * imgheight);
    rect = wxRect((width - new_width)/2,(height - new_width)/2, new_width, new_height);
    //std::cout<<std::endl<<"Ratio: "<<ratio;
    //rect = wxRect(std::abs(width - new_width)/2,std::abs(height - new_width)/2, new_width, new_height);
    maxzoomout = (double)new_width * 100.00 / (double)imgwidth;
    //std::cout<<std::endl<<"RECT: "<<rect.x<<" "<<rect.y<<" "<<rect.width<<" "<<rect.height<<std::endl;
    SetScrollbars(1,1, rect.width, rect.height, 0, 0);

    Update();
};


// EVENTS
void ImageContainer::OnDraw(wxDC& dc)
{
    //fills canvas with black
    dc.SetBackground( *wxBLACK_BRUSH );
    dc.Clear();

    // draw bitmap - centered
    if (image)
        dc.DrawBitmap(image->Scale(rect.width, rect.height, wxIMAGE_QUALITY_HIGH),
            rect.x, rect.y,
            false);
};

void ImageContainer::OnSize(wxSizeEvent& event)
{
    GetClientSize(&width, &height);

    //std::cout<<" OnSize Event triggered...---> W: "<<width<<" H: "<<height<<std::endl;
    FitToCanvas();
};

void ImageContainer::OnMouse(wxMouseEvent &event)
{
    if (event.GetWheelRotation() != 0)
    {
        //std::cout<<event.GetWheelRotation()<<std::endl;
        int nzoom = zoom + ((event.GetWheelRotation() > 0)? zoomstep : -zoomstep);


        nzoom = (nzoom > 100)? 100: (nzoom < maxzoomout)? maxzoomout : nzoom;

        //std::cout<<"Zoom: "<<zoom<< "  -> "<<nzoom<<std::endl;
        if (nzoom != zoom)
        {
            zoom = nzoom;
            if (zoom == 0)
            {
                FitToCanvas();
                return;
            }
            //zoom in/out the drawn area
            int w = (double)image->GetWidth()  * ((double)zoom / 100.00);
            int h = (double)image->GetHeight() * ((double)zoom / 100.00);
            //std::cout<<"Zoomed  "<<zoom<<"%   w: "<<w<< "  h: "<<h<<std::endl<<" CANVAS: "<<width<<" "<<height<<std::endl;

            if (w < width || h < height)
            {
                double xratio = (double) width / (double) w;
                double yratio = (double) height / (double) h;
                double ratio = xratio < yratio ? xratio : yratio;
                int new_width = (int)(ratio * w);
                int new_height = (int)(ratio * h);
                rect = wxRect(std::abs(width - new_width)/2,std::abs(height - new_width)/2, new_width, new_height);
            }
            else
            {
                rect = wxRect(0, 0 , w, h);
            }

            SetScrollbars(1, 1, rect.width, rect.height, std::abs(rect.width - width)/2, std::abs(rect.height - height)/2);
            Update();
        }
    }
};

