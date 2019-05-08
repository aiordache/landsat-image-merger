
#include "gui.hpp"

class Application : public wxApp
{
  private:
      MainFrame* frame;
  public:
    // 'Main program' equivalent
    bool OnInit()
      {
          frame = new MainFrame(NULL, wxT("Satellite Image Processing Project"));
          SetTopWindow(frame);
          frame->Show();
          return true;
      };
    int OnExit()
      {
        return 0;
      };
    ~Application()
    {
        std::cout<<"Release memory here...\n";
        //delete frame;
    }
};



// Create a new application object
IMPLEMENT_APP(Application)

