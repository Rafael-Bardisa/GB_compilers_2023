//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#include "common.h"
#include "automata.h"

#ifndef COMPILERS_LEXER_H
#define COMPILERS_LEXER_H

typedef struct lexer{
    Automata* automatas;
    int num_automatas;
} Lexer;

/**
 * create a lexer from a list of (assumes valid) filenames
 * @param automata_files
 * @param num_files
 * @return
 */
Lexer create_lexer(char** automata_files, int num_files);

/**
 * frees allocated memory of the lexer
 * @param lexer
 */
void free_lexer(Lexer* lexer);

/**
 * helper function for scan_file
 * @param lexer
 * @param contents
 * @param contents_len how many bytes in contents. If ASCII, equivalent to number of characters
 * @param outfile where to write the processed tokens
 * @return return status. 0 is good
 */
int scan_str(Lexer* lexer, char* contents, int contents_len, FILE* outfile);

/**
 * scans an entire file. Stores the contents in a buffer and calls helper function
 * @param lexer
 * @param infile the file to scan
 * @param outfile the file to store the result at. Can be stdout
 * @return status return. 0 is good
 */
int scan_file(Lexer* lexer, char* infile);

/**
 * count comparison operations performed by a lexer since its creation
 * @param lexer
 * @return sum of countop of all lexer's automatas
 */
int opcount(Lexer* lexer);

#endif //COMPILERS_LEXER_H
