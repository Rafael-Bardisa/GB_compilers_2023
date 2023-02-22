//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#ifndef COMPILERS_COMMON_H
#define COMPILERS_COMMON_H

#include <stdio.h>
#include <string.h>

//ultimate flex
#include "foreach.h"
#include "format.h"

// defining NO_FMT replaces all calls to FMT() by "", essentially deactivating the macro

#define TRUE 1
#define FALSE 0

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

#endif //COMPILERS_COMMON_H
