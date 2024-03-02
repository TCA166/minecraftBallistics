#import <stdio.h>
#import <objc/Object.h>

//I know this file should be named csvFile.h, but then everything thinks this is a C file and that annoys me

@interface csvFile : Object

@property (nonatomic, readonly) FILE* file;

+(id) alloc;
-(id) init:(const char*)fileName;
-(void) writeLine:(double)x: (double)y;
-(void) close;

@end