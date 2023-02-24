//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#ifndef COMPILERS_COMMON_H
#define COMPILERS_COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "foreach.h"
#include "format.h"

// defining NO_FMT replaces all calls to FMT() by "", essentially deactivating the macro

#define TRUE 1
#define FALSE 0

#define NARGS(...) (sizeof((char*[]){__VA_ARGS__})/sizeof(char*))
/**
 * ugly way to create and write into a buffer the string concatenations of the next n arguments.
 */
#define join(buffer, ...) char buffer[joint_len(NARGS(__VA_ARGS__), __VA_ARGS__)]; \
join_(buffer, NARGS(__VA_ARGS__), __VA_ARGS__);

#define SIGMA "\U000003A3"
#define getName(var) #var

/**
 * bool structure if needed
 */
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
size_t file_size(FILE* infile);

/**
 * join a variadic list of strings into buffer argument
 * @param buffer where to store the concatenation of all strigns
 * @param argc number of strings to concatenate
 * @param ... the strings to concatenate
 * @return same buffer pointer
 */
char* join_(char* buffer, int argc, ...);

/**
 * get joint length of all strings in variadic arguments
 * @param argc number of strings
 * @param ... the (null terminated) strings
 * @return joint size of all strings
 */
size_t joint_len(int argc, ...);

#endif //COMPILERS_COMMON_H
