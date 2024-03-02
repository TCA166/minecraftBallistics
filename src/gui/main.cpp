#include <wx/wx.h>

#include "mainFrame.hpp"

//https://docs.wxwidgets.org/3.2/page_topics.html

class app : public wxApp {
    public:
        virtual bool OnInit();
        ~app() = default;
};

wxIMPLEMENT_APP(app);

bool app::OnInit() {
    mainFrame *frame = new mainFrame();
    frame->Show(true);
    return true;
}
