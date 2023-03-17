//
// Created by Rafael Bardisa Rodes on 14/2/23.
//
#include "common.h"

#ifndef COMPILERS_PROJECT_GB_RESULT_H
#define COMPILERS_PROJECT_GB_RESULT_H

typedef enum status {
    OK = 0,
    E_FILE_NOT_FOUND,
} Status;

/**
 * factory of result types. Similar to Optional types, but provides enumeration support for error handling<br>
 * It should be only used as a return type. Cannot support pointer return values.
 */
#define result(type) struct result_##type{Status status; type value;}

/**
 * Struct to store possible error types and FILE* return values. Not very fleshed out at the moment
 */
typedef struct result_file {
    Status status;  //whether the result was successful or an error. Possible error types in enum above
    FILE* value;    //FILE* value wrapped around the status field.
}Result_file;

/**
 * Provides an error explanation given the following parameters
 * @param status Error code of the function
 * @param line_number Line number that triggered the error
 * @param trigger_function function that triggered the error
 * @param recoverable whether to exit the program or not. For now, only true is implemented
 */
void explain_error_(Status status, int line_number, char* trigger_function, bool recoverable);

#define explain_error(result_like) explain_error_(result_like.status, __LINE__, __FUNCTION__, FALSE)

/**
 * wrapper for fopen to use result type
 * @param filename file to open
 * @param mode mode to open
 * @return Result struct. If status is ok, file is okay for use
 */
Result_file file_open(char* filename, char* mode);
#endif //COMPILERS_PROJECT_GB_RESULT_H
