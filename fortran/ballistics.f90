module ballisticsMath
    use, intrinsic :: ISO_C_BINDING
    implicit none
contains

!https://en.wikipedia.org/wiki/Projectile_motion#Angle_θ_required_to_hit_coordinate_(x,_y)

real(c_double) function getAngle(v, g, x, y) bind(C, name="getAngle")
    real(c_double), intent(in) :: v, g, x, y
    real(c_double) :: angle
    angle = atan((v**2 - sqrt(v**4 - g*((g*(x**2)) + (2*y*(v**2)))))/(g*x))
    getAngle = angle
end function getAngle

!https://en.wikipedia.org/wiki/Projectile_motion#Maximum_distance_of_projectile

real(c_double) function getRange(v, g, angle) bind(C, name="getRange")
    real(c_double), intent(in) :: v, g, angle
    real(c_double) :: range
    range = (v**2)*sin(2*angle)/g
    getRange = range
end function getRange

real(c_double) function getHeight(v, g, angle, x) bind(C, name="getHeight")
    real(c_double), intent(in) :: v, g, angle, x
    real(c_double) :: height
    height = (x*tan(angle)) - ((g*(x**2))/(2*(v**2)*(cos(angle)**2)))
    getHeight = height
end function getHeight

real(c_double) function getMaxHeight(v, g, angle) bind(C, name="getMaxHeight")
    real(c_double), intent(in) :: v, g, angle
    real(c_double) :: height
    height = (v**2 * sin(angle)**2) / (2 * g)
    getMaxHeight = height
end function getMaxHeight

real(c_double) function shallowAngleOfReach(v, g, d) bind(C, name="shallowAngleOfReach")
    real(c_double), intent(in) :: v, g, d
    real(c_double) :: angle
    angle = asin((g * d) / v**2) / 2
    shallowAngleOfReach = angle
end function shallowAngleOfReach

!!TODO add function for calculating optimal angle for coordinate

!!TODO add function for calculating velocity for set angle and position

end module ballisticsMath
