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

char* join_(char* buffer, int argc, ...){
    buffer[0] = '\0';

    va_list argv;
    int i;

    // initialize argv to get data from the variable arguments
    va_start(argv, argc);

    /* access all the arguments assigned to valist */
    for (i = 0; i < argc; i++) {
    // retrieve ansi code and concatenate into buffer
    strcat(buffer, va_arg(argv, char*));
    }
    /* clean memory reserved for valist */
    va_end(argv);

    return buffer;
}

size_t joint_len(int argc, ...){
    size_t length = 1;

    va_list argv;

    // initialize argv to get data from the variable arguments
    va_start(argv, argc);

    /* access all the arguments assigned to valist */
    for (int i = 0; i < argc; i++) {
        // retrieve ansi code and concatenate into buffer
        length += strlen(va_arg(argv, char*));
    }
    /* clean memory reserved for valist */
    va_end(argv);

    return length;
}