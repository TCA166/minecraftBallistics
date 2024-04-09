/*!
 @file csvFile.h
 @brief This file contains the definition for the objC csvFile object.
*/

typedef void* csvFile;

/* 
this is all terrible
but I guess I do owe an explanation. Obj C as D or C++ stores internally methods as functions with mangled names.
Unfortunately this scheme is not compatible with C, so I have to use extern "C" to avoid name mangling.
I also have to provide the two SECRET APPLE™ arguments to the functions, which are the object (equivalent to this or self)
and the command (equivalent to the method name). Apparently command can be also a message? and you can do cool things with it.
No clue tho I would look it up in the standard IF THERE WAS ONE.
*/

/*!
 @brief Allocates a new csvFile object.
 @return A new csvFile object.
*/
#define csvFile_alloc() _c_csvFile__alloc(NULL, "alloc")
/*!
 @brief Initializes a csvFile object.
 @param self The csvFile object to initialize.
 @param filename The filename to write to.
*/
#define csvFile_init(self, filename) _i_csvFile__init_(self, "init:", filename)
/*!
 @brief Writes a line to the csv file.
 @param self The csvFile object.
 @param x The x value.
 @param y The y value.
*/
#define csvFile_writeLine(self, x, y) _i_csvFile__writeLine__(self, "writeLine::", x, y)
/*!
 @brief Closes the csv file.
 @param self The csvFile object.
*/
#define csvFile_close(self) _i_csvFile__close(self, "close")

#define csvFile_free(self) free(self)

extern "C" {
    csvFile _c_csvFile__alloc(csvFile self, const char* _cmd);

    csvFile _i_csvFile__init_(csvFile self, const char* _cmd, const char* filename);

    void _i_csvFile__writeLine__(csvFile self, const char* _cmd, double x, double y);

    void _i_csvFile__close(csvFile self, const char* _cmd);
}
