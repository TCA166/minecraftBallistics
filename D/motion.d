module motionModule;

extern (C) { //horrible hack to get over a lack of a macroprocessor in D
    mixin(import("ballistics.h"));
}

import core.runtime;
import std.math;

bool runtimeInitialized = false;

//https://dlang.org/spec/cpp_interface.html#using_d_classes_from_cpp

extern (C++){
    class motionFactory{
        public:
            this(double velocity, double gravity, double angle){
                this.velocity = velocity;
                this.gravity = gravity;
                this.angle = angle;
            }
            this(double velocity, double gravity, double x, double y){
                this(velocity, gravity, getAngle(&velocity, &gravity, &x, &y));
            }
            double getVelocity() const{
                return velocity;
            }
            void setVelocity(double velocity){
                this.velocity = velocity;
            }
            double getGravity() const{
                return gravity;
            }
            double getCurrentRange() const{
                return getRange(&velocity, &gravity, &angle);
            }
            double getCurrentAngle() const{
                return this.angle;
            }
            void setAngle(double angle){
                this.angle = angle;
            }
            void setAngle(double x, double y){
                double newAngle = getAngle(&velocity, &gravity, &x, &y);
                if(isNaN(newAngle)){
                    throw new Exception("Invalid position");
                }
                this.angle = newAngle;
            }
            double getY(double x) const{
                return getHeight(&velocity, &gravity, &angle, &x);
            }
            motion getMotion(double step) const{
                //FIXME hack it even more by allocating the memory in C? ASSEMBLY PERHAPS?!??!?!!
                if(!runtimeInitialized){ //horrible hack to get over the fact that D needs to be initialized before allocating any memory
                    runtimeInitialized = true;
                    Runtime.initialize();
                }
                return new motion(velocity, gravity, angle, step);
            }
        private:
            double velocity;
            double gravity;
            double angle;
    }

    class motion : motionFactory{
        public:
            this(double velocity, double gravity, double angle, double step){
                super(velocity, gravity, angle);
                this.current = 0;
                this.step = step;
                this.range = getRange(&velocity, &gravity, &angle);
            }
            this(double velocity, double gravity, double x, double y, double step){
                this(velocity, gravity, getAngle(&velocity, &gravity, &x, &y), step);
            }
            bool empty() const{
                return current > range;
            }
            double next(){
                double result = front();
                popFront();
                return result;
            }
            double length(){
                return (range - current) / step;
            }
        private:
            double current;
            const double step;
            const double range;
            double front() const{
                return getY(current);
            }
            void popFront(){
                current += step;
            }
    }
}
