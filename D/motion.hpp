
class motion;

class motionFactory {
    public:
        motionFactory(double velocity, double gravity, double angle);
        motionFactory(double velocity, double gravity, double x, double y);
        double getVelocity() const;
        void setVelocity(double velocity);
        double getGravity() const;
        double getCurrentRange() const;
        double getCurrentAngle() const;
        void setAngle(double angle);
        void setAngle(double x, double y);
        double getY(double x) const;
        motion* getMotion(double step) const;
    private: //the inclusion of this in the header is crucial for size calculations
        double velocity;
        double gravity;
        double angle;
        double dummy;
};

class motion : public motionFactory{
    public:
        motion(double velocity, double gravity, double angle, double step);
        motion(double velocity, double gravity, double x, double y, double step);
        bool empty() const;
        double next();
        double length() const;
    private:
        double current;
        const double step;
        const double range;
};
