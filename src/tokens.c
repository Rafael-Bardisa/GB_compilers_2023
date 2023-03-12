//
// Created by Rafael Bardisa Rodes on 31/1/23.
//
#include "tokens.h"

Token create_token(const char* lexeme, Category cat){
    Token token = {.lexeme = lexeme, .category = cat};
    return token;
}

void print_token(Token* token, FILE *fd){
    // string representation of token->category
    char* repr = cat_to_str(&token->category);

    fprintf(fd, "<%s, %s> ", token->lexeme, repr);
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
        case CAT_TYPE:
            repr = "CAT_TYPE";
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
    else if (!strcmp(str, "CAT_TYPE")){
        category = CAT_TYPE;
    }
    else {
        category = CAT_NONRECOGNIZED;
    }

    return category;
}

Stack_Token Stack_Token_create(size_t capacity){
    Stack stack = {
            .capacity = capacity,
            .size = 0,
            .element_size = sizeof (Token),
            .contents = calloc(capacity, sizeof (Token)),
    };
    Stack_Token result = {
            .stack = stack,
    };

    return result;
}

void Stack_Token_delete(Stack_Token* stack, bool owned){
    //TODO cast internal data pointer as pointer to tokens and free all of them, memory management
    if (owned){
        //Token* data = (Token*) stack.stack.contents;
        //for (int i = 0; i < stack.stack.size; i++){
        //}
    }
    free(stack->stack.contents);
}

//TODO memory management
Option_Token Stack_Token_pop(Stack_Token* stack){
    Option_Token result = {0};
    Option_void inner_result = pop(&stack->stack);
    if (!inner_result.ok) return result;

    //dereference inner pointer and get the token at the top position of the stack
    result.ok = TRUE;
    result.value = *(Token*)inner_result.value;

    return result;
}

int Stack_Token_push(Stack_Token* stack, Token token){
    return push(&stack->stack, (void*) &token);
}