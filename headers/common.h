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

/*
typedef union Iter{
    int i;
    char c;
    double d;
    float f;
} iter;
*/

#endif //COMPILERS_COMMON_H
