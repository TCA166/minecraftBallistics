#include <wx/wx.h>

#include "motionGraph.hpp"

class mainFrame : public wxFrame {
    public:
        mainFrame();
        ~mainFrame();
    protected:
		wxButton* findAngle;
        wxButton* findOptimal;
		wxStaticText* velocityText;
		wxSlider* velocitySlider;
        wxStaticText* angleText;
		wxSlider* angleSlider;
        wxCheckBox* resizeCheck;
        wxStaticBitmap* graphPanel;
        bool selectingAngle;
        bool selectingOptimal;
        motionGraph* graph;
        /*!
         @brief Regraphs the bitmap graph
        */
        void regraph();
        virtual void mainFrameOnSize(wxSizeEvent& event);
		virtual void findAngleOnButtonClick(wxCommandEvent& event);
        virtual void findOptimalOnButtonClick(wxCommandEvent& event);
		virtual void velocitySliderOnScroll(wxScrollEvent& event);
		virtual void angleSliderOnScroll(wxScrollEvent& event);
        virtual void graphPanelOnLeftDown(wxMouseEvent& event);
        virtual void mainFrameOnLeftUp(wxMouseEvent& event);
        virtual void resizeCheckOnCheckBox(wxCommandEvent& event);
        virtual void unsetAngleSelect();
        void setAngle(double angle);
        void setVelocity(double velocity);
    private:
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
};