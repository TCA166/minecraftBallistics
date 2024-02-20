#include <stdlib.h>
#include <stdio.h>

#include "fortran/ballistics.h"
#include "constants.h"

int main(int argc, char** argv){
    double v, x, g, y;
    g = minecraftGravity;
    if(argc < 2){ //help case
        printf("Usage: %s <maxArrowVelocity> <x> <y>\n", argv[0]);
        return EXIT_FAILURE;
    }
    else if(argc == 2){ //we check max range for velocity
        v = atof(argv[1]);
        double angle = 0.90;
        double distance = getRange(&v, &g, &angle);
        printf("The distance is %f\n", distance);
        return EXIT_SUCCESS;
    }
    else if(argc > 3){
        v = atof(argv[3]);
    }
    else{ //argc == 3
        v = maxArrowVelocity;
    }
    x = atof(argv[1]);
    y = atof(argv[2]);
    double angle = getAngle(&v, &g, &x, &y);
    printf("The angle is %f", angle);
    double distance = getRange(&v, &g, &angle);
    printf(" and the maximum distance is %f\n", distance);
    return 0;
}
