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

// dumb function to concat two strings
char* add_scn(const char* input_file){
    char output_file[250];
    int i = 0;
    char* scn = "scn";
    while (input_file[i] != '\0' ){
        output_file[i] = input_file[i];
        i++;
    }
    for(int j = 0; j<3; j++){
        output_file[i] = scn[j];
        i++;
    }
    output_file[i] = '\0';

    return output_file;
}