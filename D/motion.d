module motionModule;

extern (C) { //horrible hack to get over a lack of a macroprocessor in D
    mixin(import("ballistics.h"));
}

import std.math : isNaN;
import core.stdc.stdlib : malloc;
import std.conv : emplace;

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
            this(double velocity, double gravity, long range){
                double rangeD = cast(double)range;
                this(velocity, gravity, shallowAngleOfReach(&velocity, &gravity, &rangeD));
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
            double getPeakHeight() const{
                return getMaxHeight(&velocity, &gravity, &angle);
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
            void setAngle(long range){
                double rangeD = cast(double)range;
                this.angle = shallowAngleOfReach(&velocity, &gravity, &rangeD);
            }
            double getY(double x) const{
                return getHeight(&velocity, &gravity, &angle, &x);
            }
            motion getMotion(double step) const{
                /*
                D for all it's good points has a terrible allocator (suposedly) that is very slow (suposedly).
                Additionally the allocator needs to be initialized because it utilizes GC.
                Now we don't really do that, and GC is something we neither want nor use.
                So we go around it by using the C allocator, with all that entails.
                */
                size_t size = __traits(classInstanceSize, motion);
                void[] ptr = malloc(size)[0..size];
                return emplace!motion(ptr, velocity, gravity, angle, step);
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
                this.range = this.getCurrentRange();
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
            double getOffset() const{
                return current;
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
