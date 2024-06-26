#include <wx/wx.h>
#include <wx/rawbmp.h>

#include <exception>

#include "mainFrame.hpp"
#include "../constants.h"

#include "../objC/csvFile.h"

const wxSize controlSize = wxSize(200, -1);
const int border = 5;
const unsigned int tickSize = 10;
const unsigned char midGray = 128;
const unsigned char lightGray = 64;

mainFrame::mainFrame() : wxFrame(NULL, wxID_ANY, "Minecraft arrow ballistics calculator") {
    selectingAngle = false;
    selectingOptimal = false;
    this->SetSize(wxSize(1000, 600));
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

        findOptimal = new wxButton(this, wxID_ANY, wxT("Find Optimal"), wxDefaultPosition, controlSize, 0);
        bSizer7->Add(findOptimal, 0, wxALL, border);

        findVelocity = new wxButton(this, wxID_ANY, wxT("Find Velocity"), wxDefaultPosition, controlSize, 0);
        bSizer7->Add(findVelocity, 0, wxALL, border);

        velocityText = new wxStaticText(this, wxID_ANY, wxT("Velocity"), wxDefaultPosition, controlSize, 0);
        velocityText->Wrap(-1);
        bSizer7->Add(velocityText, 0, wxALL, border);

        velocitySlider = new wxSlider(this, wxID_ANY, maxArrowVelocity, 0, maxArrowVelocity, wxDefaultPosition, controlSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_MIN_MAX_LABELS);
        bSizer7->Add(velocitySlider, 0, wxALL, border);

        angleText = new wxStaticText(this, wxID_ANY, wxT("Angle"), wxDefaultPosition, controlSize, 0);
        angleText->Wrap(-1);
        bSizer7->Add(angleText, 0, wxALL, border);

        angleSlider = new wxSlider(this, wxID_ANY, 90, 5, 155, wxDefaultPosition, controlSize, wxSL_HORIZONTAL|wxSL_LABELS|wxSL_MIN_MAX_LABELS);
        bSizer7->Add(angleSlider, 0, wxALL, border);

        resizeCheck = new wxCheckBox(this, wxID_ANY, wxT("Auto rescale"), wxDefaultPosition, controlSize, 0);
        bSizer7->Add(resizeCheck, 0, wxALL, border);

        exportButton = new wxButton(this, wxID_ANY, wxT("Export to CSV"), wxDefaultPosition, controlSize, 0);
        bSizer7->Add(exportButton, 0, wxALL, border);

        graph = new motionGraph(maxArrowVelocity, minecraftGravity, 0.9, m_width - controlSize.x - (border * 4), m_height - (border * 12));
        graphPanel = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(graph->GetWidth(), graph->GetHeight()), 0);
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
        findOptimal->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainFrame::findOptimalOnButtonClick), NULL, this);
        findVelocity->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainFrame::findVelocityOnButtonClick), NULL, this);
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
        resizeCheck->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(mainFrame::resizeCheckOnCheckBox), NULL, this);
        exportButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainFrame::exportButtonClick), NULL, this);
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
    //TODO expand
}

void mainFrame::setAngle(double angle){
    graph->setAngle(angle);
    angleSlider->SetValue((int)(angle * 100));
    regraph();
}

void mainFrame::setVelocity(double velocity){
    graph->setVelocity(velocity);
    velocitySlider->SetValue((int)velocity);
    regraph();
}

void mainFrame::exportButtonClick(wxCommandEvent& event){
    csvFile file = csvFile_alloc();
    csvFile_init(file, "output.csv");
    for(int i = 0; i < graph->getRange() - 1; i++){
        csvFile_writeLine(file, i, graph->getY(i));
    }
    csvFile_close(file);
    csvFile_free(file);
    SetStatusText("Exported to output.csv");
}

void mainFrame::unsetAngleSelect(){
    if(!selectingAngle && !selectingOptimal && !selectingVelocity){
        return;
    }
    selectingAngle = false;
    selectingOptimal = false;
    selectingVelocity = false;
    SetStatusText("");
    wxSetCursor(wxCursor(wxCURSOR_DEFAULT));
}

void mainFrame::graphPanelOnLeftDown(wxMouseEvent& event){
    if(!selectingAngle && !selectingOptimal && !selectingVelocity){
        return;
    }
    double x = event.GetX() / graph->getScale();
    double y = (graph->GetHeight() - event.GetY()) / graph->getScale();
    try{
        if(selectingAngle){
            graph->setAngle(x, y);
            angleSlider->SetValue((int)(graph->getAngle() * 100));
        }
        else if(selectingOptimal){
            graph->setOptimal(x, y);
            velocitySlider->SetValue((int)graph->getVelocity());
            angleSlider->SetValue((int)(graph->getAngle() * 100));
        }
        else if(selectingVelocity){
            double oldV = graph->getVelocity();
            graph->setVelocity(x, y);
            if(graph->getVelocity() > maxArrowVelocity){
                graph->setVelocity(oldV);
                throw std::exception();
            }
            velocitySlider->SetValue((int)graph->getVelocity());
        }
    }
    catch(...){
        SetStatusText("Invalid position");        
        return;
    }
    unsetAngleSelect();
    regraph();
}

void mainFrame::findAngleOnButtonClick(wxCommandEvent& event){
    selectingAngle = true;
    wxSetCursor(wxCursor(wxCURSOR_CROSS));
    SetStatusText("Select a point on the graph");
}

void mainFrame::findOptimalOnButtonClick(wxCommandEvent& event){
    selectingOptimal = true;
    wxSetCursor(wxCursor(wxCURSOR_CROSS));
    SetStatusText("Select a point on the graph");
}

void mainFrame::findVelocityOnButtonClick(wxCommandEvent& event){
    selectingVelocity = true;
    wxSetCursor(wxCursor(wxCURSOR_CROSS));
    SetStatusText("Select a point on the graph");
}

void mainFrame::mainFrameOnLeftUp(wxMouseEvent& event){
    unsetAngleSelect();
}

void mainFrame::mainFrameOnSize(wxSizeEvent& event){
    
}

void mainFrame::velocitySliderOnScroll(wxScrollEvent& event){
    graph->setVelocity(velocitySlider->GetValue());
    regraph();
}

void mainFrame::angleSliderOnScroll(wxScrollEvent& event) {
    graph->setAngle((double)angleSlider->GetValue() / 100.0);
    regraph();
}

void mainFrame::resizeCheckOnCheckBox(wxCommandEvent& event){
    graph->setReSize(resizeCheck->IsChecked());
}

void mainFrame::regraph(){
    graphPanel->SetBitmap(*graph);
}

void mainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void mainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a calculator tool that calculates possible trajectories for minecraft arrows.\nYou can play around with the sliders, or using buttons click on different parts of the graph and determine slider settings.", "About", wxOK | wxICON_INFORMATION);
}
