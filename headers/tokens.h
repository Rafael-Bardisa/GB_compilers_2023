//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#ifndef COMPILERS_TOKENS_H
#define COMPILERS_TOKENS_H

#include "common.h"

// default print to stdout for error checking
#define TKPRINT(a) print_token(a, stdout)

/**
 * Enumeration of possible token types
 */
typedef enum category{
    CAT_NONRECOGNIZED = 0,
    CAT_NUMBER,
    CAT_IDENTIFIER,
    CAT_KEYWORD,
    CAT_LITERAL,
    CAT_OPERAND,
    CAT_TYPE,
    CAT_SPECIALCHAR,
} Category;

//TODO memory management
typedef struct token {
    char* lexeme;   //the actual string value of the token
    Category category;  //the category of the token
} Token;

/**
 * Creates a token from a lexeme string and a cat Category
 * @param lexeme
 * @param cat
 * @return the corresponding Token
 */
Token create_token(const char* lexeme, Category cat);

/**
 * Returns the string representation of the given category
 * @param category
 * @return char* containing the string representation of the category
 */
char* cat_to_str(const Category* category);

/**
 * Returns the enum category value of str
 * @param str
 * @return a category
 */
Category str_to_cat(const char* str);

/**
 * Converts a token into a readable string and prints it to the given file descriptor\n
 * 0 is stdin, 1 is stdout, 2 is stderr\n
 * any FILE* can be used with the return value of fileno(file)
 *
 * @param token a pointer to a valid token struct
 * @param fd the file descriptor to write into
 * @return the string representation of the given token
 */
void print_token(Token* token, FILE *fd);

/**
 * optional type for tokens
 */
typedef optional(Token) Option_Token;

/**
 * stack restricted to only contain tokens. Special functions are used for correct data storage and retrieval
 */
typedef struct stack_token {
    Stack stack;
} Stack_Token;

/**
 * create a stack of tokens
 * @param capacity how many tokens can be stored in the stack
 * @return an empty stack of tokens
 */
Stack_Token Stack_Token_create(size_t capacity);

/**
 * free memory associated with the token stack
 * @param owned whether the stack holds the only references to the tokens in the stack or not. If true, the function must free each individual token
 */
void Stack_Token_delete(Stack_Token* stack, bool owned);

/**
 * pop operation for stack of tokens
 * @param stack the token stack
 * @return an optional token. It is ok if the stack had tokens in it
 */
Option_Token Stack_Token_pop(Stack_Token* stack);

/**
 * push operation for stack of tokens
 * @param stack the token stack
 * @param token the token to push into the stack
 * @return whether or not the push was successful. 0 is ok.
 */
int Stack_Token_push(Stack_Token* stack, Token token);
#endif //COMPILERS_TOKENS_H
