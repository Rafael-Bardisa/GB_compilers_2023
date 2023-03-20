//
// Created by Rafael Bardisa Rodes on 12/3/23.
//

#ifndef COMPILERS_PROJECT_GB_PARSER_H
#define COMPILERS_PROJECT_GB_PARSER_H

#include "automata_sr.h"

#define PARSER_CAPACITY 64

typedef struct parser{
    Token* file_as_tokens;  //token representation of a file
    Stack_Token stack;  //stack to store read tokens

    Automata_SR automata; //it makes sense to only have an automata for a grammar
}Parser;

/**
 * create a parser from file sources
 */
Parser Parser_new(char* token_file, char* goto_file, char* rules_file, char* states_file);

/**
 * parse a cscn file to see if the contents are accepted by the parser grammar
 * @param parser
 * @param filename
 */
void parse(Parser* parser, const char* filename);

/**
 * how many tokens are in the given string
 * @param string
 * @return
 */
size_t num_tokens_in_string(const char* string);

/**
 * parse a string into its valid  allocated tokens
 * @param string a string with some tokens
 * @return
 */
Token* str_to_tokens(const char* string);

/**
 * open and read from a token file into a valid token pointer
 */
int parse_file_to_tokens(char* filename, Token* token_list);

#endif //COMPILERS_PROJECT_GB_PARSER_H
