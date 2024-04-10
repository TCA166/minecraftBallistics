
.global sqrt_asm
sqrt_asm: # float sqrt(float x)
    sqrtsd %xmm0, %xmm0
    ret
