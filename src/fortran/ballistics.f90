module ballisticsMath
    use, intrinsic :: ISO_C_BINDING
    implicit none
contains

!https://en.wikipedia.org/wiki/Projectile_motion#Angle_θ_required_to_hit_coordinate_(x,_y)

real(c_double) function calculateAngle(v, g, x, y) bind(C, name="calculateAngle")
    real(c_double), intent(in) :: v, g, x, y
    real(c_double) :: angle
    angle = atan((v**2 - sqrt(v**4 - g*((g*(x**2)) + (2*y*(v**2)))))/(g*x))
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
    v = sqrt(g * (y + sqrt(y**2 + x**2)))
    lowestVelocity = v
end function lowestVelocity

!!FIXME i dont think this is right
real(c_double) function calculateVelocity(angle, g, x, y) bind(C, name="calculateVelocity")
    real(c_double), intent(in) :: angle, g, x, y
    real(c_double) :: v, l, a, b
    l = g * x * tan(angle)
    a = (g**2) * (x**2)
    b = 2 * g * y
    v = sqrt(-((l**2) * b) + (2 * (l**3)) - (a * b) + (2 * a * b)) / (-b + (2*l))
    calculateVelocity = v
end function calculateVelocity

end module ballisticsMath
