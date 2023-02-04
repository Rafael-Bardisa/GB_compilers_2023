//
// Created by Rafael Bardisa Rodes on 31/1/23.
//
#include "tokens.h"


void print_token(Token* token, int fd){
    // string representation of token->category
    char* repr = cat_to_str(&token->category);

    dprintf(fd, "<%s, %s>", token->lexeme, repr);
}


char* cat_to_str(const Category* category) {

    char* repr;
    switch(*category){
        case CAT_LITERAL:
            repr = "CAT_LITERAL";
            break;
        case CAT_KEYWORD:
            repr = "CAT_KEYWORD";
            break;
        case CAT_IDENTIFIER:
            repr = "CAT_IDENTIFIER";
            break;
        case CAT_NUMBER:
            repr = "CAT_NUMBER";
            break;
        case CAT_OPERAND:
            repr = "CAT_OPERAND";
            break;
        case CAT_SPECIALCHAR:
            repr = "CAT_SPECIALCHAR";
            break;
        default:
            repr = "CAT_UNRECOGNIZED";
    }
    // this is fine because it returns a pointer to a string literal, which is burned in the binary of the program
    return repr;
}

Category str_to_cat(const char* str) {
    Category category;

    // cant do switch statement on char*
    if (!strcmp(str, "CAT_LITERAL")){
        category = CAT_LITERAL;
    }
    else if (!strcmp(str, "CAT_KEYWORD")){
        category = CAT_KEYWORD;
    }
    else if (!strcmp(str, "CAT_IDENTIFIER")){
        category = CAT_IDENTIFIER;
    }
    else if (!strcmp(str, "CAT_NUMBER")){
        category = CAT_NUMBER;
    }
    else if (!strcmp(str, "CAT_OPERAND")){
        category = CAT_OPERAND;
    }
    else if (!strcmp(str, "CAT_SPECIALCHAR")){
        category = CAT_SPECIALCHAR;
    }
    else {
        category = CAT_NONRECOGNIZED;
    }

    return category;
}