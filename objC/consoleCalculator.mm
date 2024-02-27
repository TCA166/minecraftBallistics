//We don't have access to the weird apple/nextstep/gnustep environment so we use the standard C library :)
#import <stdlib.h>
#import <stdio.h>

#import "../D/motion.hpp"

#import "../constants.h"

int main(int argc, const char * argv[]){
    double v, x, g, y;
    g = minecraftGravity;
    if(argc < 2){ //help case
        printf("Usage: %s <maxArrowVelocity> <x> <y>\n", argv[0]);
        return EXIT_FAILURE;
    }
    else if(argc == 2){ //we check max range for velocity
        v = atof(argv[1]);
        double angle = 0.90;
        motionFactory* mf = new motionFactory(v, g, angle);
        double range = mf->getCurrentRange();
        printf("Max range for velocity %f is %f\n", v, range);
        return EXIT_SUCCESS;
    }
    else if(argc > 3){
        v = atof(argv[3]);
        //TODO handle additional arguments. Definetly want to incorporate a csv dump function
    }
    else{ //argc == 3
        v = maxArrowVelocity;
    }
    x = atof(argv[1]);
    y = atof(argv[2]);
    motionFactory* mf = new motionFactory(v, g, x, y);
    double angle = mf->getCurrentAngle();
    printf("The angle is %f", angle);
    double distance = mf->getCurrentRange();
    printf(" and the maximum distance is %f\n", distance);
    return 0;
}
