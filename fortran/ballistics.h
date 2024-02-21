
/*!
 @brief Gets the Angle one needs to shoot a projectile to hit a target
 @param velocity The velocity of the projectile
 @param g The acceleration due to gravity
 @param x The x coordinate of the target
 @param y The y coordinate of the target
 @return The angle in radians, or -NaN if the result is impossible
*/
double getAngle(const double* velocity, const double* g, const double* x, const double* y);

/*!
 @brief Gets the range of a projectile
 @param v The velocity of the projectile
 @param g The acceleration due to gravity
 @param theta The angle of the projectile
 @return The range of the projectile
*/
double getRange(const double* velocity, const double* g, const double* theta);

/*!
 @brief Gets the height of a projectile at a given x coordinate
 @param velocity The velocity of the projectile
 @param g The acceleration due to gravity
 @param theta The angle of the projectile
 @param x The x coordinate of the projectile
 @return The height of the projectile
*/
double getHeight(const double* velocity, const double* g, const double* theta, const double* x);

/*!
 @brief Gets the maximum height of a projectile
 @param velocity The velocity of the projectile
 @param g The acceleration due to gravity
 @return The maximum height of the projectile
*/
double getMaxHeight(const double* velocity, const double* g);

/*!
 @brief Calculates the shallow angle of reach
 @param velocity The velocity of the projectile
 @param g The acceleration due to gravity
 @param distance The distance to the target
 @return The angle in radians, or -NaN if the result is impossible
*/
double shallowAngleOfReach(const double* velocity, const double* g, const double* distance);
