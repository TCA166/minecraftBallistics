#include <wx/wx.h>

class app : public wxApp {
    public:
        virtual bool OnInit();
        ~app() = default;
};

enum{
    ID_Hello = 1
};