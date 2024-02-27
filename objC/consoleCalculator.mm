//We don't have access to the weird apple/nextstep/gnustep environment so we use the standard C library :)
#import <stdlib.h>
#import <stdio.h>
#import <string.h>

#import "csvFile.h"

#import "../D/motion.hpp"

#import "../constants.h"

int main(int argc, const char * argv[]){
    bool csv = false;
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
    motionFactory* mf = new motionFactory(v, g, x, y);
    double angle = mf->getCurrentAngle();
    printf("The angle is %f", angle);
    double distance = mf->getCurrentRange();
    printf(" and the maximum distance is %f\n", distance);
    //FIXME objC class allocation shenangians
    if(csv){
        id instance = [[csvFile new] init];
        [instance writeLine:angle :distance];
        double offset = 0.05;
        motion* m = mf->getMotion(offset);
        for(double val = m->next(); !m->empty(); val = m->next()){
            [instance writeLine:offset :val];
            offset += 0.05;
        }
    }
    return 0;
}
