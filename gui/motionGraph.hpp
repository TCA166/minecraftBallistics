#include <wx/bitmap.h>
#include "../D/motion.hpp"

class motionGraph : public wxBitmap, public motionFactory{
    public:
        motionGraph(double velocity, double gravity, double angle, int width, int height);
        void setAngle(...);
        void setVelocity(...);
    private:
        wxColour background = wxColour(64, 64, 64);
        wxColour accent = wxColour(128, 128, 128);
        uint8_t tickSize = 10;
        unsigned int scale;
        void reScale();
        void regraph();
};