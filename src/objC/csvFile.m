#include <stdio.h>
#include <stdlib.h>

#include "../C/csvWriter.h"

#import <objc/Object.h>

@interface csvFile : Object{
    csv* file;
}

+(id) alloc;
-(id) init:(const char*)fileName;
-(void) writeLine:(double)x: (double)y;
-(void) close;

@end

@implementation csvFile : Object

+(id) alloc {
    id new = nil;
    new = calloc(1, class_getInstanceSize(self));
    new->class_pointer = self;
    return new;
}

- (void) writeLine:(double)x: (double)y {
    const double* values[] = {&x, &y};
    writeCSVvalues(2, (const void**)values, "%f", self->file);
}

- (void) close {
    fclose(self->file->file);
}

- (id) init:(const char*)fileName {
    if(self) {
        self->file = newCSV(fileName, ',', '\n');
    }
    return self;
}

@end