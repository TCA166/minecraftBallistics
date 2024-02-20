#include <wx/wx.h>
#include <wx/rawbmp.h>

#include "mainFrame.hpp"
#include "guiCalculator.hpp"
#include "../constants.h"

const wxSize controlSize = wxSize(200, -1);
const int border = 5;
const unsigned int graphScale = 3;
const unsigned int tickSize = 10;
const uint8_t midGray = 128;
const uint8_t lightGray = 64;

mainFrame::mainFrame() : wxFrame(NULL, wxID_ANY, "Minecraft arrow ballistics calculator") {
    motionF = new motionFactory(maxArrowVelocity, minecraftGravity, 0.90);
    selectingAngle = false;
    this->SetSize(wxSize(800, 500));
    {//create and initialize file menu
        wxMenu *menuFile = new wxMenu;
        menuFile->Append(wxID_EXIT);

        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);

        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "&File");
        menuBar->Append(menuHelp, "&Help");

        SetMenuBar(menuBar);
    }
    
    {//text at the bottom
        CreateStatusBar();
        //SetStatusText("Welcome to wxWidgets!");
    }

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    { //initialize the window components
        wxFlexGridSizer* fgSizer3;
        fgSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
        fgSizer3->SetFlexibleDirection(wxBOTH);
        fgSizer3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

        wxBoxSizer* bSizer7;
        bSizer7 = new wxBoxSizer(wxVERTICAL);

        findAngle = new wxButton(this, wxID_ANY, wxT("Find Angle"), wxDefaultPosition, controlSize, 0);
        bSizer7->Add(findAngle, 0, wxALL, border);

        velocityText = new wxStaticText(this, wxID_ANY, wxT("Velocity"), wxDefaultPosition, controlSize, 0);
        velocityText->Wrap(-1);
        bSizer7->Add(velocityText, 0, wxALL, border);

        velocitySlider = new wxSlider(this, wxID_ANY, maxArrowVelocity, 0, maxArrowVelocity, wxDefaultPosition, controlSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_MIN_MAX_LABELS);
        bSizer7->Add(velocitySlider, 0, wxALL, border);

        angleText = new wxStaticText(this, wxID_ANY, wxT("Angle"), wxDefaultPosition, controlSize, 0);
        angleText->Wrap(-1);
        bSizer7->Add(angleText, 0, wxALL, border);

        angleSlider = new wxSlider(this, wxID_ANY, 45, 0, 180, wxDefaultPosition, controlSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_MIN_MAX_LABELS);
        bSizer7->Add(angleSlider, 0, wxALL, border);

        graph = new wxBitmap(m_width - controlSize.x - (border * 4), m_height - (border * 12));
        graphPanel = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(m_width - controlSize.x - (border * 4), m_height - (border * 12)), 0);
        regraph();

        fgSizer3->Add(bSizer7, 1, wxEXPAND, border);
        fgSizer3->Add(graphPanel, 2, wxALL, border);
        
        this->SetSizer(fgSizer3);
        this->Layout();
    }
	
	this->Centre(wxBOTH);

    {//event bindings
        this->Connect(wxEVT_SIZE, wxSizeEventHandler(mainFrame::mainFrameOnSize));
        findAngle->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainFrame::findAngleOnButtonClick), NULL, this);
        velocitySlider->Connect(wxEVT_SCROLL_TOP, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
        velocitySlider->Connect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
        velocitySlider->Connect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
        velocitySlider->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
        velocitySlider->Connect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
        velocitySlider->Connect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
        velocitySlider->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
        velocitySlider->Connect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
        velocitySlider->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
        angleSlider->Connect(wxEVT_SCROLL_TOP, wxScrollEventHandler(mainFrame::angleSliderOnScroll), NULL, this);
        angleSlider->Connect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(mainFrame::angleSliderOnScroll), NULL, this);
        angleSlider->Connect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(mainFrame::angleSliderOnScroll), NULL, this);
        angleSlider->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(mainFrame::angleSliderOnScroll), NULL, this);
        angleSlider->Connect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(mainFrame::angleSliderOnScroll), NULL, this);
        angleSlider->Connect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(mainFrame::angleSliderOnScroll), NULL, this);
        angleSlider->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(mainFrame::angleSliderOnScroll), NULL, this);
        angleSlider->Connect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(mainFrame::angleSliderOnScroll), NULL, this);
        angleSlider->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(mainFrame::angleSliderOnScroll), NULL, this);
        graphPanel->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(mainFrame::graphPanelOnLeftDown), NULL, this);
        this->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(mainFrame::mainFrameOnLeftUp), NULL, this);
        //Menu events
        Bind(wxEVT_MENU, &mainFrame::OnAbout, this, wxID_ABOUT);
        Bind(wxEVT_MENU, &mainFrame::OnExit, this, wxID_EXIT);
    }
}

mainFrame::~mainFrame(){
    // Disconnect Events
	findAngle->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainFrame::findAngleOnButtonClick), NULL, this);
	velocitySlider->Disconnect(wxEVT_SCROLL_TOP, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
	velocitySlider->Disconnect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
	velocitySlider->Disconnect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
	velocitySlider->Disconnect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
	velocitySlider->Disconnect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
	velocitySlider->Disconnect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
	velocitySlider->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
	velocitySlider->Disconnect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
	velocitySlider->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(mainFrame::velocitySliderOnScroll), NULL, this);
}

void mainFrame::setAngle(double angle){
    motionF->setAngle(angle);
    angleSlider->SetValue((int)(angle * 100));
    regraph();
}

void mainFrame::setVelocity(double velocity){
    motionF->setVelocity(velocity);
    velocitySlider->SetValue((int)velocity);
    regraph();
}

void mainFrame::unsetAngleSelect(){
    if(!selectingAngle){
        return;
    }
    selectingAngle = false;
    SetStatusText("");
    wxSetCursor(wxCursor(wxCURSOR_DEFAULT));
}

void mainFrame::graphPanelOnLeftDown(wxMouseEvent& event){
    if(!selectingAngle){
        return;
    }
    double x = event.GetX() / graphScale;
    double y = (graph->GetHeight() - event.GetY()) / graphScale;
    unsetAngleSelect();
    try{
        motionF->setAngle(x, y);
    }
    catch(...){
        SetStatusText("Invalid position");        
        return;
    }
    angleSlider->SetValue((int)(motionF->getCurrentAngle() * 100));
    regraph();
}

void mainFrame::findAngleOnButtonClick(wxCommandEvent& event){
    selectingAngle = true;
    wxSetCursor(wxCursor(wxCURSOR_CROSS));
    SetStatusText("Select a point on the graph");
}

void mainFrame::mainFrameOnLeftUp(wxMouseEvent& event){
    unsetAngleSelect();
}

void mainFrame::mainFrameOnSize(wxSizeEvent& event){
    
}

void mainFrame::velocitySliderOnScroll(wxScrollEvent& event){
    motionF->setVelocity(velocitySlider->GetValue());
    regraph();
}

void mainFrame::angleSliderOnScroll(wxScrollEvent& event) {
    motionF->setAngle((double)angleSlider->GetValue() / 100.0);
    regraph();
}

void mainFrame::regraph(){
    //get the pixel iterator
    wxNativePixelData data = wxNativePixelData(*graph);
    wxNativePixelData::Iterator p(data);
    for(long y = graph->GetHeight(); y > 0; y--){ //foreach row from top to bottom
        wxNativePixelData::Iterator rowStart = p;
        uint8_t r = lightGray, g = lightGray, b = lightGray; //pixel will be light gray
        if(y % (graphScale * tickSize) == 0){ //unless the row is one in twenty
            r = midGray;
            g = midGray;
            b = midGray;
        }
        for(long x = 0; x < graph->GetWidth(); x++, p++){
            if(x % (graphScale * tickSize) == 0){ //or column is one in twenty
                p.Red() = midGray;
                p.Green() = midGray;
                p.Blue() = midGray;
            }
            else{ //set the pixel color
                p.Red() = r;
                p.Green() = g;
                p.Blue() = b;
            }
        }
        p = rowStart;
        p.OffsetY(data, 1);
    }
    motion* thisMotion = motionF->getMotion(1.0 / (float)graphScale);
    p = wxNativePixelData::Iterator(data);
    for(double val = thisMotion->next(); !thisMotion->empty(); val = thisMotion->next(), p++){
        double y = graph->GetHeight() - (val * graphScale);
        p.OffsetY(data, y);
        p.Red() = 255;
        p.Green() = 0;
        p.Blue() = 0;
        p.OffsetY(data, -y);
    }
    graphPanel->SetBitmap(*graph);
}

void mainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void mainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a calculator tool that calculates possible trajectories for minecraft arrows.\nYou can play around with the sliders, or using buttons click on different parts of the graph and determine slider settings.", "About", wxOK | wxICON_INFORMATION);
}
