//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#ifndef COMPILERS_COMMON_H
#define COMPILERS_COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

//ultimate flex
#include "foreach.h"
#include "format.h"

// defining NO_FMT replaces all calls to FMT() by "", essentially deactivating the macro

#define TRUE 1
#define FALSE 0

#define NARGS(...) (sizeof((char*[]){__VA_ARGS__})/sizeof(char*))
/**
 * create and write into buffer the string concatenations of the next n arguments.
 */
#define join(buffer, ...) char buffer[joint_len(NARGS(__VA_ARGS__), __VA_ARGS__)]; \
join_(buffer, NARGS(__VA_ARGS__), __VA_ARGS__);

#define SIGMA "\U000003A3"
#define getName(var) #var


typedef enum bool_{
    false = FALSE,
    true = TRUE,
} bool;

/**
 * Given a file, return the length of the file in bytes (equivalent to characters if file is encoded in ASCII)<br>
 * Resets the file position indicator back to the start of the file!
 * @param infile pointer to the file to calculate the length of
 * @return the length of the file in characters
 * TODO error checking
 */
int file_size(FILE* infile);

/**
 * join a variadic list of strings into buffer argument
 * @param buffer
 * @param argc
 * @param ...
 * @return
 */
char* join_(char* buffer, int argc, ...);

/**
 * get joint length of all strings in variadic arguments
 * @param buffer
 * @param argc
 * @param ...
 * @return
 */
size_t joint_len(int argc, ...);

#endif //COMPILERS_COMMON_H
