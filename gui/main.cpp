#include <wx/wx.h>

#include "guiCalculator.hpp"
#include "mainFrame.hpp"

//https://docs.wxwidgets.org/3.2/page_topics.html

wxIMPLEMENT_APP(app);

bool app::OnInit() {
    mainFrame *frame = new mainFrame();
    frame->Show(true);
    return true;
}
