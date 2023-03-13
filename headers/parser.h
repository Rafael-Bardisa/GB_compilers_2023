//
// Created by Rafael Bardisa Rodes on 12/3/23.
//

#ifndef COMPILERS_PROJECT_GB_PARSER_H
#define COMPILERS_PROJECT_GB_PARSER_H

#include "automata_sr.h"

typedef struct parser{
    Stack_Token stack;  //stack to store read tokens

    Automata_SR automata; //it makes sense to only have an automata for a grammar
}Parser;

#endif //COMPILERS_PROJECT_GB_PARSER_H
