#include <stdio.h>
#include <stdlib.h>

#import <objc/Object.h>

@interface csvFile : Object{
    FILE* file;
}

@property (nonatomic, readwrite, assign) FILE* file;

+(id) alloc;
-(id) init:(const char*)fileName;
-(void) writeLine:(double)x: (double)y;
-(void) close;

@end

@implementation csvFile : Object

@synthesize file;

+(id) alloc {
    id new = nil;
    new = calloc(1, class_getInstanceSize(self));
    new->class_pointer = self;
    return new;
}

- (void) writeLine:(double)x: (double)y {
    fprintf(self.file, "%f,%f\n", x, y);
}

- (void) close {
    fclose(self.file);
}

- (id) init:(const char*)fileName {
    if (self) {
        self.file = fopen(fileName, "w");
    }
    return self;
}

@end