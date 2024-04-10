module altMath
    ! basically header file for the assembly functions
    use, intrinsic :: ISO_C_BINDING
    implicit none
    interface
        function sqrt_asm(x) bind(C, name="sqrt_asm")
            use, intrinsic :: ISO_C_BINDING
            real(c_double) :: sqrt_asm
            real(c_double), intent(in) :: x
        end function sqrt_asm
    end interface
end module