#include <stdio.h>

#import <objc/Object.h>

@interface csvFile : Object{
    FILE* file;
}

@property (nonatomic, readwrite, assign) FILE* file;

-(id) initWithFile:(const char*)fileName;
-(void) writeLine:(double)x: (double)y;
-(void) close;

@end

@implementation csvFile

@synthesize file;

- (void) writeLine:(double)x: (double)y {
    fprintf(self.file, "%f,%f\n", x, y);
}

- (void) close {
    fclose(self.file);
}

- (id) initWithFile:(const char*)fileName {
    if (self) {
        self.file = fopen(fileName, "w");
    }
    return self;
}

@end