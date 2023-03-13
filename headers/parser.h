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

/**
 * parse a cscn file to see if the contents are accepted by the parser grammar
 * @param parser
 * @param filename
 */
void parse(Parser* parser, const char* filename);

#endif //COMPILERS_PROJECT_GB_PARSER_H
