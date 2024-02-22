/*!
 @defgroup motion motion
 @brief Object interface for projectile motion
 @details Object oriented interface for calculating the position of a projectile at a given time
*/

class motion;

/*!
 @brief A factory class for creating motion instances and storing physical properties of a projectile
 @addtogroup motion
*/
class motionFactory {
    public:
        motionFactory(double velocity, double gravity, double angle);
        motionFactory(double velocity, double gravity, double x, double y);
        motionFactory(double velocity, long range);
        /*!
         @brief Get the starting velocity of the projectile
         @return the starting velocity of the projectile
        */
        double getVelocity() const;
        /*!
         @brief Set the starting velocity of the projectile
         @param velocity the starting velocity of the projectile
        */
        void setVelocity(double velocity);
        /*!
         @brief Get the gravity acting upon of the projectile
         @return the gravity
        */
        double getGravity() const;
        /*!
         @brief Calculates the range of the projectile
         @return the range of the projectile
        */
        double getCurrentRange() const;
        /*!
         @brief Get the angle of the projectile
         @return the angle of the projectile
        */
        double getCurrentAngle() const;
        /*!
         @brief Set the angle of the projectile
         @param angle the angle of the projectile
        */
        void setAngle(double angle);
        /*!
         @brief Set the angle of the projectile by calculating the angle needed to hit a target
         @param x the x coordinate of the target
         @param y the y coordinate of the target
        */
        void setAngle(double x, double y);
        /*!
         @brief Sets the angle to reach the set range
         @param range the range to reach
        */
        void setAngle(long range);
        /*!
         @brief Gets the y coordinate of the projectile at a given x coordinate
         @param x the x coordinate
         @return the y coordinate
        */
        double getY(double x) const;
        /*!
         @brief Creates a motion instance based on the current state
         @param step the step size of the motion
         @note the caller is responsible for freeing the returned instance using libc's free
         @return a motion instance based on the current state
        */
        motion* getMotion(double step) const;
    private: //the inclusion of this in the header is crucial for size calculations
        double velocity;
        double gravity;
        double angle;
        double dummy;
};

/*!
 @brief A class for calculating the position of a projectile at a given time
 @addtogroup motion
*/
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
