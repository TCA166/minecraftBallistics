#import <stdio.h>
#import <objc/Object.h>

@interface csvFile : Object{
    FILE* file;
}

@property (nonatomic, readonly) FILE* file;

+(id) alloc;
-(id) init:(const char*)fileName;
-(void) writeLine:(double)x: (double)y;
-(void) close;

@end