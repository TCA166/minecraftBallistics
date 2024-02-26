#include "motionGraph.hpp"
#include <wx/rawbmp.h>

/*
Here's what happens.
D doesn't have multi inheritance as a feature, so it doesn't generate constructors for it.
However C++ expects to have different constructors for different multi inheritance cases. In our case it's looking for motionFactoryC2 while D doesn't create one because it has no clue wtf is multi inheritance.
So we need to do D's job for it in a linker script
*/

motionGraph::motionGraph(double velocity, double gravity, double angle, int width, int height) : motionGraph(velocity, gravity, angle, width, height, 3, true){

}

motionGraph::motionGraph(double velocity, double gravity, double angle, int width, int height, uint8_t lineWidth, bool reSize) : wxBitmap(width, height), motionFactory(velocity, gravity, angle){
    this->lineWidth = lineWidth;
    reScale();
    this->reSize = reSize;
}

void motionGraph::regraph(){
    wxNativePixelData data(*this);
    wxNativePixelData::Iterator p(data);
    for(long y = this->GetHeight(); y > 0; y--){ //foreach row from top to bottom
        wxNativePixelData::Iterator rowStart = p;
        wxColour r = background; //pixel will be background color
        int tickScaled = (int)(scale * tickSize);
        if(y % tickScaled == 0){ //unless the row is one in twenty
            r = accent;
        }
        for(long x = 0; x < this->GetWidth(); x++, p++){
            if(x % tickScaled == 0){ //or column is one in twenty
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
    unsigned int prevY = 0;
    unsigned short colNum = 0;
    for(double val = thisMotion->next(); !thisMotion->empty(); val = thisMotion->next(), p++, colNum++){
        unsigned int y = this->GetHeight() - (val * scale) - (lineWidth / 2);
        p.OffsetY(data, y);
        uint8_t i = 0;
        //TODO add interpolation
        while(i < lineWidth && y + i < this->GetHeight()){
            p.Red() = 255;
            p.Green() = 0;
            p.Blue() = 0;
            p.OffsetY(data, 1);
            i++;
        }
        p.OffsetY(data, -y - i);
        prevY = y;
        if(colNum > this->GetWidth()){
            break;
        }
    }
    free(thisMotion);
}

void motionGraph::reScale(){
    if(reSize){
        double scale = this->GetWidth() / (this->getCurrentRange() * 1.1);
        if(scale * this->getPeakHeight() * 1.1 > this->GetHeight()){
            scale = this->GetHeight() / (this->getPeakHeight() * 1.1);
        }
        this->scale = scale;
    }
    regraph();
}

void motionGraph::setAngle(double angle){
    motionFactory::setAngle(angle);
    reScale();
}

void motionGraph::setAngle(double x, double y){
    motionFactory::setAngle(x, y);
    reScale();
}

void motionGraph::setAngle(long range){
    motionFactory::setAngle(range);
    reScale();
}

void motionGraph::setVelocity(double velocity){
    motionFactory::setVelocity(velocity);
    reScale();
}

double motionGraph::getScale() const{
    return scale;
}

void motionGraph::setReSize(bool reSize){
    reScale();
    this->reSize = reSize;
}

void motionGraph::setOptimal(double x, double y){
    motionFactory::setOptimal(x, y);
    reScale();
}
