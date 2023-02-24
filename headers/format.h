//
// Created by Rafael Bardisa Rodes on 1/2/23.
//

#ifndef COMPILERS_FORMAT_H
    #define COMPILERS_FORMAT_H

    #ifdef NO_FMT   //disables the FMT macro
        #define FMT(...) ""
    #else

        #include <stdarg.h>
        #include <string.h>

        /**
         * Count the number of char* in variadic arguments, auxiliary for FMT macro
         */
        #define FARGS(...)  (sizeof((char*[]){__VA_ARGS__})/sizeof(char*))

        /**
         * Generates an ANSI format string from a variadic list of defined format style macros.<br>
         * example use:
         * @code
         * printf("%sHello, %sWorld!%s", FMT(RED, WHITE_BG), FMT(BLUE, BLACK_BG), FMT(CLEAR));
         * @endcode
         */
        #define FMT(...) \
        format((char[4*FARGS(__VA_ARGS__) + sizeof(FMT_START) + sizeof(FMT_END) + 1]){""}, FARGS(__VA_ARGS__), __VA_ARGS__)

        #define FMT_START "\x1B["
        #define FMT_END "m"

        // ansi flags for text styling, there's a lot of them

        //black
        #define BLACK ";30"
        //red
        #define RED ";31"
        //green
        #define GREEN ";32"
        //yellow
        #define YELLOW ";33"
        //blue
        #define BLUE ";34"
        //magenta
        #define MAGENTA ";35"
        //cyan
        #define CYAN ";36"
        //bright gray
        #define GRAY_B ";37"

        //black background
        #define BLACK_BG ";40"
        //red background
        #define RED_BG ";41"
        //green background
        #define GREEN_BG ";42"
        //yellow background
        #define YELLOW_BG ";43"
        //blue background
        #define BLUE_BG ";44"
        //magenta background
        #define MAGENTA_BG ";45"
        //cyan background
        #define CYAN_BG ";46"
        //bright gray background
        #define GRAY_BG_B ";47"

        //gray
        #define GRAY ";90"
        //bright red
        #define RED_B ";91"
        //bright green
        #define GREEN_B ";92"
        //bright yellow
        #define YELLOW_B ";93"
        //bright blue
        #define BLUE_B ";94"
        //bright magenta
        #define MAGENTA_B ";95"
        //bright cyan
        #define CYAN_B ";96"
        //white
        #define WHITE ";97"

        //gray background
        #define GRAY_BG ";100"
        //bright red background
        #define RED_BG_B ";101"
        //bright green background
        #define GREEN_BG_B ";102"
        //bright yellow background
        #define YELLOW_BG_B ";103"
        //bright blue background
        #define BLUE_BG_B ";104"
        //bright magenta background
        #define MAGENTA_BG_B ";105"
        //bright cyan background
        #define CYAN_BG_B ";106"
        //white background
        #define WHITE_BG ";107"

        #define DASH ";9"

        #define BOLD ";1"
        #define ITALICS ";3"
        // I can't explain this one
        #define REVERSE ";7"
        #define CLEAR ";0"

        // underline light
        #define UNDERLINE_L ";4"
        // underline heavy
        #define UNDERLINE_H ";21"

        /**
         * creates a format string based on input parameters.
         * @param argc the number of ansi flags to use
         * @param buffer the buffer to write the format string into. A size of 64 should be enough for most reasonable uses
         * @param ... the variadic ansi flags to use. Examples include RED, BLUE, DASH, etc
         * @return the same pointer buffer, for ease of use in printf functions
         */
        char* format(char* buffer, int argc, ...);
    #endif  //NO_FMT

#endif //COMPILERS_FORMAT_H
