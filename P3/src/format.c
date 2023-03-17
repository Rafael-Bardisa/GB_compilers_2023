//
// Created by Rafael Bardisa Rodes on 1/2/23.
//

// file is blank if NO_FMT
#ifndef NO_FMT
    #include "format.h"

    char* format(char* buffer, int argc, ...){
        buffer[0] = '\0';

        va_list argv;
        int i;

        // initialize argv to get data from the variable arguments
        va_start(argv, argc);

        strcat(buffer, FMT_START);
        /* access all the arguments assigned to valist */
        for (i = 0; i < argc; i++) {
            // retrieve ansi code and concatenate into buffer
            strcat(buffer, va_arg(argv, char*));
        }
        strcat(buffer, FMT_END);

        /* clean memory reserved for valist */
        va_end(argv);

        return buffer;

    }
#endif //NO_FMT