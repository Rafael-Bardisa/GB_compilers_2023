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

char* concat(char* input_file){
    char output_file[250];
    int i = 0;
    while (&input_file[i] != '\n' ){

    }

    return output_file;
}