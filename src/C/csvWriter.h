#include <stdio.h>

typedef struct{
    FILE* file;
    size_t headerCount;
    char** headers;
    size_t lineCount;
    char delimiter;
    char newline;
} csv;

/*!
 @brief Creates a new csv file
 @param filename the name of the file
 @param delimiter the delimiter of the file
 @param newline the newline character of the file
 @return the csv file
*/
csv* newCSV(const char* filename, char delimiter, char newline);

/*!
 @brief Writes n strings to a csv file
 @param n the number of strings to write
 @param values the strings to write
 @param c the csv file to write to
 @return the number of characters written
*/
size_t writeCSVline(size_t n, const char** values, csv* c);

/*!
 @brief Writes a header to a csv file
 @param n the number of strings to write
 @param values the strings to write
 @param c the csv file to write to
 @return the number of characters written
*/
size_t setHeader(size_t n, char** values, csv* c);

/*!
 @brief Writes n values to a csv file
 @param n the number of values to write
 @param values the values to write
 @param format the format of the values
 @param c the csv file to write to
 @return the number of characters written
*/
size_t writeCSVvalues(size_t n, const void** values, const char* format, csv* c);
