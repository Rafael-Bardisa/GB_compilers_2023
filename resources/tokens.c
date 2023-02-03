//
// Created by Rafael Bardisa Rodes on 31/1/23.
//
#include "tokens.h"


void printToken(Token* token, int fd){
    // string representation of token->category
    char* repr = catToStr(&token->category);

    dprintf(fd, "<%s, %s>", token->lexeme, repr);
}


char* catToStr(const Category* category) {

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
