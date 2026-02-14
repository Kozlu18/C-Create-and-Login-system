#include "MyApp.h"
#include "MyFrame.h"

#include <wx/wx.h>

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("App");
    frame->SetSize(800, 600);
    frame->Center();
    frame->Show(true);
    return true;
}
