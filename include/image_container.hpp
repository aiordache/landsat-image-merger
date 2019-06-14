#include <wx/wx.h>
#include <wx/image.h>

class ImageContainer : public wxScrolledWindow
{
    private:
        // bitmap to be drawn on the canvas
        wxImage*  image  = NULL;
        // message to be drawn when image is loading
        wxString* message = NULL;
        // extracted image area to be drawn
        wxRect    rect   = wxRect(0,0,0,0);
        // zoom 0%
        int    zoom      = 0;
        int    zoomstep  = 10;// scale 5%
        int    maxzoomout= 0;

        // canvas dimensions
        int       width  = 1200;
        int       height = 600;


        void OnDraw(wxDC& dc);
        void OnSize(wxSizeEvent& event);
        void OnMouse(wxMouseEvent &event);

        void FitToCanvas();

    public:
    	ImageContainer(wxWindow* parent, wxWindowID id);
    	~ImageContainer();

    	void SetImage(wxImage* img);
    	void SetMessage(wxString* msg);
    	void Clear();
};
