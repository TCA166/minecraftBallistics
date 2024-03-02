//We don't have access to the weird apple/nextstep/gnustep environment so we use the standard C library :)
#import <stdlib.h>
#import <stdio.h>
#import <string.h>

#import "csvFileHeader.m"

#import "../D/motion.hpp"

#import "../constants.h"

int main(int argc, const char * argv[]){
    bool csv = false;
    double v, x, g, y;
    g = minecraftGravity;
    if(argc < 2){ //help case
        printf("Usage: %s <x> <y> <arrow velocity>\n", argv[0]);
        return EXIT_FAILURE;
    }
    else if(argc == 2){ //we check max range for velocity
        v = atof(argv[1]);
        double angle = 0.90;
        motionFactory* mf = new motionFactory(v, g, angle);
        double range = mf->getRange();
        printf("Max range for velocity %f is %f\n", v, range);
        return EXIT_SUCCESS;
    }
    else if(argc > 3){
        v = atof(argv[3]);
        for(int i = 4; i < argc; i++){
            if(strcmp(argv[i], "-csv") == 0){
                csv = true;
            }
        }
    }
    else{ //argc == 3
        v = maxArrowVelocity;
    }
    x = atof(argv[1]);
    y = atof(argv[2]);
    motionFactory* mf;
    @try{
        mf = new motionFactory(v, g, x, y);
    }
    @catch(...){
        printf("Invalid position\n");
        return EXIT_FAILURE;
    }
    double angle = mf->getAngle();
    double distance = mf->getRange();
    printf("The angle is %f and the maximum distance is %f\n", angle, distance);
    if(csv){
        id instance = [[csvFile alloc] init: "motion.csv"];
        [instance writeLine:angle :distance];
        double offset = 0.05;
        motion* m = mf->getMotion(offset);
        for(double val = m->next(); !m->empty(); val = m->next()){
            [instance writeLine:offset :val];
            offset += 0.05;
        }
        [instance close];
    }
    return 0;
}
