#include "motionGraph.hpp"
#include <wx/rawbmp.h>
/*
Here's what happens.
D doesn't have multi inheritance as a feature, so it doesn't generate constructors for it.
However C++ expects to have different constructors for different multi inheritance cases. In our case it's looking for motionFactoryC2 while D doesn't create one because it has no clue wtf is multi inheritance.
So we need to do D's job for it in a linker script
*/

motionGraph::motionGraph(double velocity, double gravity, double angle, int width, int height) : wxBitmap(width, height), motionFactory(velocity, gravity, angle){
    reScale();
}

void motionGraph::regraph(){
    wxNativePixelData data(*this);
    wxNativePixelData::Iterator p(data);
    for(long y = this->GetHeight(); y > 0; y--){ //foreach row from top to bottom
        wxNativePixelData::Iterator rowStart = p;
        wxColour r = background; //pixel will be background color
        if(y % (scale * tickSize) == 0){ //unless the row is one in twenty
            r = accent;
        }
        for(long x = 0; x < this->GetWidth(); x++, p++){
            if(x % (scale * tickSize) == 0){ //or column is one in twenty
                p.Red() = accent.Red();
                p.Green() = accent.Green();
                p.Blue() = accent.Blue();
            }
            else{ //set the pixel color
                p.Red() = r.Red();
                p.Green() = r.Green();
                p.Blue() = r.Blue();
            }
        }
        p = rowStart;
        p.OffsetY(data, 1);
    }
    motion* thisMotion = this->getMotion(1.0 / (float)scale);
    p = wxNativePixelData::Iterator(data);
    for(double val = thisMotion->next(); !thisMotion->empty(); val = thisMotion->next(), p++){
        double y = this->GetHeight() - (val * scale);
        p.OffsetY(data, y);
        p.Red() = 255;
        p.Green() = 0;
        p.Blue() = 0;
        p.OffsetY(data, -y);
    }
    free(thisMotion);
}

void motionGraph::reScale(){
    double range = getCurrentRange();
    scale = this->GetWidth() / range;
    regraph();
}

void motionGraph::setAngle(double angle){
    motionFactory::setAngle(angle);
    regraph();
}

void motionGraph::setAngle(double x, double y){
    motionFactory::setAngle(x, y);
    regraph();
}

void motionGraph::setAngle(long range){
    motionFactory::setAngle(range);
    regraph();
}

void motionGraph::setVelocity(double velocity){
    motionFactory::setVelocity(velocity);
    regraph();
}
