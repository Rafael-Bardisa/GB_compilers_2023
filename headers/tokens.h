//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#ifndef COMPILERS_TOKENS_H
#define COMPILERS_TOKENS_H

#include "common.h"

// default print to stdout for error checking
#define TKPRINT(a) printToken(a, 1)

typedef enum category{
    CAT_NUMBER,
    CAT_IDENTIFIER,
    CAT_KEYWORD,
    CAT_LITERAL,
    CAT_OPERAND,
    CAT_SPECIALCHAR,
    CAT_NONRECOGNIZED,
} Category;

typedef struct token {
    char* lexeme;
    Category category;
} Token;
/**
 * Returns the string representation of the given category
 * @param category
 * @return char* containing the string representation of the category
 */
char* catToStr(const Category* category);

/**
 * Converts a token into a readable string and prints it to the given file descriptor\n
 * 0 is stdin, 1 is stdout, 2 is stderr\n
 * any FILE* can be used with the return value of fileno(file)
 *
 * @param token a pointer to a valid token struct
 * @param fd the file descriptor to write into
 * @return the string representation of the given token
 */
void printToken(Token* token, int fd);
#endif //COMPILERS_TOKENS_H
