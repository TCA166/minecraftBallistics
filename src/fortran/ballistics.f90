module ballisticsMath
    use, intrinsic :: ISO_C_BINDING
    use altMath
    implicit none
contains

!https://en.wikipedia.org/wiki/Projectile_motion#Angle_θ_required_to_hit_coordinate_(x,_y)

real(c_double) function calculateAngle(v, g, x, y) bind(C, name="calculateAngle")
    real(c_double), intent(in) :: v, g, x, y
    real(c_double) :: angle
    angle = atan((v**2 - sqrt_asm(v**4 - g*((g*(x**2)) + (2*y*(v**2)))))/(g*x))
    calculateAngle = angle
end function calculateAngle

!https://en.wikipedia.org/wiki/Projectile_motion#Maximum_distance_of_projectile

real(c_double) function calculateRange(v, g, angle) bind(C, name="calculateRange")
    real(c_double), intent(in) :: v, g, angle
    real(c_double) :: range
    range = (v**2)*sin(2*angle)/g
    calculateRange = range
end function calculateRange

real(c_double) function calculateHeight(v, g, angle, x) bind(C, name="calculateHeight")
    real(c_double), intent(in) :: v, g, angle, x
    real(c_double) :: height
    height = (x*tan(angle)) - ((g*(x**2))/(2*(v**2)*(cos(angle)**2)))
    calculateHeight = height
end function calculateHeight

real(c_double) function calculateMaxHeight(v, g, angle) bind(C, name="calculateMaxHeight")
    real(c_double), intent(in) :: v, g, angle
    real(c_double) :: height
    height = (v**2 * sin(angle)**2) / (2 * g)
    calculateMaxHeight = height
end function calculateMaxHeight

real(c_double) function shallowAngleOfReach(v, g, d) bind(C, name="shallowAngleOfReach")
    real(c_double), intent(in) :: v, g, d
    real(c_double) :: angle
    angle = asin((g * d) / v**2) / 2
    shallowAngleOfReach = angle
end function shallowAngleOfReach

real(c_double) function lowestVelocity(g, x, y) bind(C, name="lowestVelocity")
    real(c_double), intent(in) :: g, x, y
    real(c_double) :: v
    v = sqrt_asm(g * (y + sqrt_asm(y**2 + x**2)))
    lowestVelocity = v
end function lowestVelocity

real(c_double) function calculateVelocity(angle, g, x, y) bind(C, name="calculateVelocity")
    real(c_double), intent(in) :: angle, g, x, y
    real(c_double) :: v, a, b, c
    a = g * x * tan(angle)
    b = -1 * (g**2) * (x**2)
    c = -2 * g * y
    v = sqrt_asm(((a**2) * c) + (2 * (a**3)) - (b * c) - (2 * b * a)) / ((2*a) + c)
    calculateVelocity = v
end function calculateVelocity

real(c_double) function getMaxHeight(angle, range) bind(C, name="getMaxHeight")
    real(c_double), intent(in) :: angle, range
    real(c_double) :: height
    height = range * tan(angle) / 4
    getMaxHeight = height
end function getMaxHeight

end module ballisticsMath
