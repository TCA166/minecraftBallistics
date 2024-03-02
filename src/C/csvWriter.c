#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "csvWriter.h"

csv* newCSV(const char* filename, char delimiter, char newline){
    csv* c = malloc(sizeof(csv));
    c->file = fopen(filename, "w");
    c->delimiter = delimiter;
    c->newline = newline;
    c->lineCount = 0;
    c->headerCount = 0;
    c->headers = NULL;
    return c;
}

size_t writeCSVvalues(size_t n, const double* values, const char* format, csv* c){
    size_t written = 0;
    for(size_t i = 0; i < n; i++){
        fprintf(c->file, format, values[i]);
        if(i < n - 1){
            written += fwrite(&c->delimiter, 1, 1, c->file);
        }
    }
    written += fwrite(&c->newline, 1, 1, c->file);
    c->lineCount++;
    return written;
}

size_t writeCSVline(size_t n, const char** values, csv* c){
    size_t written = 0;
    for(size_t i = 0; i < n; i++){
        written += fwrite(values[i], 1, strlen(values[i]), c->file);
        if(i < n - 1){
            written += fwrite(&c->delimiter, 1, 1, c->file);
        }
    }
    written += fwrite(&c->newline, 1, 1, c->file);
    c->lineCount++;
    return written;
}

size_t setHeader(size_t n, char** values, csv* c){
    c->headerCount = n;
    c->headers = values;
    return writeCSVline(n, (const char**)values, c);
}
