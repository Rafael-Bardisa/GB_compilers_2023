//
// Created by Rafael Bardisa Rodes on 13/2/23.
//

#include "common.h"

int file_size(FILE* infile){

    fseek(infile, 0L, SEEK_END);

    //narrowing conversion, is only a problem for very large files
    int size = ftell(infile);
    rewind(infile);

    return size;
}