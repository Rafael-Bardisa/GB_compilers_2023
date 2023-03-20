//
// Created by Rafael Bardisa Rodes on 31/1/23.
//
#include "tokens.h"

Token create_token(char* lexeme, Category cat){
    Token token = {.lexeme = lexeme, .category = cat};
    return token;
}

Token allocate_token(const char* lexeme, size_t lexeme_len, Category cat){
    //allocate and copy into heap memory the contents of the lexeme string
    char* heap_allocated = calloc(lexeme_len+1, sizeof(char));
    memcpy(heap_allocated, lexeme, lexeme_len * sizeof (char));

    //create and return a token
    return create_token(heap_allocated, cat);
}

void Token_free(Token* token){
    free(token->lexeme);
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

Token read_token(char* string, size_t string_size){
    //< is [0], > is [string_size-1]
    int i = 0;

    for(i = string_size - 1; string[i] != ' '; i--);

    size_t lexeme_len = i - 2;
    size_t category_len = string_size - i - 2;

    char* category = calloc(category_len + 1, sizeof(char));
    memcpy(category, &string[i+1], category_len);


    Token result = allocate_token(&string[1], lexeme_len, str_to_cat(category));

    free(category);
    return result;
}

int parse_str_to_tokens(char* file_contents, size_t file_contents_len, Token* token_list){
    int i, j, current_offset = 0, token_index = 0;
    int valid_tokens = 0;
    while(TRUE) {

        for (i = current_offset; file_contents[i] != '<' && i < file_contents_len; i++);
        for (j = i; file_contents[j] != '>' && j < file_contents_len; j++);
        //j = i implies if i = file_contents_len then j = file_contents_len
        if (j == file_contents_len) return valid_tokens;

        token_list[token_index] = read_token(&file_contents[i], j - i + 1);
        token_index++;
        valid_tokens++;
        current_offset = j;
    }

    //aaaaa
}

Stack_Token Stack_Token_create(size_t capacity){
    Stack_Token result = {
            .stack = Stack_create(capacity, sizeof (Token)),
            .maximum_size_reached = 0,
    };

    return result;
}

void Stack_Token_delete(Stack_Token* stack){
    for(int i = 0; i < stack->stack.size; i++){
        Token_free(&stack->stack.contents[i]);
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
    //TODO error handling
    //need to check for dangling tokens and free them if found
    //if we are writing data where a token was previously stored
    stack->maximum_size_reached = stack->maximum_size_reached > stack->stack.size ? stack->maximum_size_reached : stack->stack.size;

    if(stack->stack.size < stack->maximum_size_reached){
        Token_free(&stack->stack.contents[stack->stack.size]);
    }

    return push(&stack->stack, (void*) &token);
}