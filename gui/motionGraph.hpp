#include <wx/bitmap.h>
#include "../D/motion.hpp"

/*!
 @defgroup motionGraph motionGraph
*/

/*!
 @brief A graph that displays the motion of a projectile
 @addtogroup motionGraph
*/
class motionGraph : public wxBitmap, public motionFactory{
    public:
        /*!
         @brief Creates a motion graph
         @param velocity the starting velocity of the projectile
         @param gravity the gravity acting upon the projectile
         @param angle the angle of the projectile
         @param width the width of the graph
         @param height the height of the graph
         @param lineWidth the width of the projectile line
         @param reSize whether or not to resize the graph after initialization
        */
        motionGraph(double velocity, double gravity, double angle, int width, int height, uint8_t lineWidth, bool reSize);
        /*!
         @brief Creates a motion graph using default cosmetic settings
         @param velocity the starting velocity of the projectile
         @param gravity the gravity acting upon the projectile
         @param angle the angle of the projectile
         @param width the width of the graph
         @param height the height of the graph
        */
        motionGraph(double velocity, double gravity, double angle, int width, int height);
        /*!
         @brief Sets the angle of the projectile explicitly
         @param angle the angle of the projectile
        */
        void setAngle(double angle);
        /*!
         @brief Sets the angle of the projectile by selecting a point on the graph
         @param x the x coordinate of the point
         @param y the y coordinate of the point
        */
        void setAngle(double x, double y);
        /*!
         @brief Sets the angle of the projectile to reach a given range
         @param range the range to reach
        */
        void setAngle(long range);
        /*!
         @brief Sets the velocity of the projectile
         @param velocity the velocity of the projectile
        */
        void setVelocity(double velocity);
        /*!
         @brief Gets the scale of the graph
         @return the scale of the graph
        */
        double getScale() const;
        void setOptimal(double x, double y);
        void setReSize(bool reSize);
    private:
        wxColour background = wxColour(64, 64, 64);
        wxColour accent = wxColour(128, 128, 128);
        uint8_t tickSize = 10;
        uint8_t lineWidth = 1;
        double scale;
        bool reSize = true;
        void reScale();
        void regraph();
};