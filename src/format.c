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

        // calculate available memory in buffer available for ANSI codes
        int buffer_len = FMT_BUF_SIZE - strlen(FMT_START) - strlen(FMT_END) - 1;

        // initialize argv to get data from the variable arguments
        va_start(argv, argc);

        strcat(buffer, FMT_START);
        /* access all the arguments assigned to valist */
        for (i = 0; i < argc; i++) {

            // retrieve ansi code and substract length to available length to prevent overflows
            char* code = va_arg(argv, char*);
            buffer_len -= strlen(code);

            // concatenate ansi code if there's space available in the buffer, else break out of loop
            if(buffer_len >= 0) strcat(buffer, code);
            else break;
        }
        strcat(buffer, FMT_END);

        /* clean memory reserved for valist */
        va_end(argv);

        return buffer;

    }
#endif //NO_FMT