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

end module ballisticsMath
