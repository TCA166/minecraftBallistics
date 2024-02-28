/*!
 @defgroup ballistics Ballistics
 @brief Functions for calculating the trajectory of a projectile
 @details Functional interface for Fortran module `ballistics`
*/

/*!
 @brief Gets the Angle one needs to shoot a projectile to hit a target
 @param velocity The velocity of the projectile
 @param g The acceleration due to gravity
 @param x The x coordinate of the target
 @param y The y coordinate of the target
 @return The angle in radians, or -NaN if the result is impossible
 @addtogroup ballistics
*/
double getAngle(const double* velocity, const double* g, const double* x, const double* y);

/*!
 @brief Gets the range of a projectile
 @param v The velocity of the projectile
 @param g The acceleration due to gravity
 @param theta The angle of the projectile
 @return The range of the projectile
 @addtogroup ballistics
*/
double getRange(const double* velocity, const double* g, const double* theta);

/*!
 @brief Gets the height of a projectile at a given x coordinate
 @param velocity The velocity of the projectile
 @param g The acceleration due to gravity
 @param theta The angle of the projectile
 @param x The x coordinate of the projectile
 @return The height of the projectile
 @addtogroup ballistics
*/
double getHeight(const double* velocity, const double* g, const double* theta, const double* x);

/*!
 @brief Gets the maximum height of a projectile
 @param velocity The velocity of the projectile
 @param g The acceleration due to gravity
 @param theta The angle of the projectile
 @return The maximum height of the projectile
 @addtogroup ballistics
*/
double getMaxHeight(const double* velocity, const double* g, const double* theta);

/*!
 @brief Calculates the shallow angle of reach
 @param velocity The velocity of the projectile
 @param g The acceleration due to gravity
 @param distance The distance to the target
 @return The angle in radians, or -NaN if the result is impossible
 @addtogroup ballistics
*/
double shallowAngleOfReach(const double* velocity, const double* g, const double* distance);

/*!
 @brief Calculates the lowest velocity needed to hit a target
 @param g the acceleration due to gravity
 @param x the x coordinate of the target
 @param y the y coordinate of the target
 @return The lowest velocity needed to hit the target
*/
double lowestVelocity(const double* g, const double* x, const double* y);

/*!
 @brief Calculates the velocity needed to hit a target at a given angle
 @param theta the angle of the projectile
 @param g the acceleration due to gravity
 @param x the x coordinate of the target
 @param y the y coordinate of the target
 @return The velocity needed to hit the target
*/
double getVelocity(const double* theta, const double* g, const double* x, const double* y);
