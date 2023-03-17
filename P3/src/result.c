//
// Created by Rafael Bardisa Rodes on 24/2/23.
//

#include "result.h"
#include <stdlib.h>

char* status_to_str(Status status){
    switch (status){
        case E_FILE_NOT_FOUND:
            return "ERROR: FILE NOT FOUND";
        default:
            return "";
    }
}

void explain_error_(Status status, int line_number, char* trigger_function, bool recoverable){
    fprintf(stderr,
            "%s at line %i:\t%s%s%s",
            trigger_function,
            line_number,
            FMT(RED),
            status_to_str(status),
            FMT(CLEAR));

    if (!recoverable){
        exit(0);
    }
}

Result_file file_open(char* filename, char* mode){
    FILE *file = fopen(filename, mode);
    Result_file res = {
            .status = file ? OK : E_FILE_NOT_FOUND,
            .value = file,
    };
    return res;
}

