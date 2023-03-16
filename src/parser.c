//
// Created by Rafael Bardisa Rodes on 12/3/23.
//

#include "parser.h"
#include "tokens.h"

void parse(Parser* parser, const char* filename){

}

size_t num_tokens_in_string(const char* string){

}


Token* str_to_tokens(const char* string){

}

void into_tokens(char* file_contents, Token* token_list){
    int i = 0;
    int num_token = 0;
    size_t file_len = strlen(file_contents);
    char* current_token = calloc(file_len  + 1, sizeof(char));

    while (i < file_len ) {
        //tokens are separated by space
        if (file_contents[i] == ' ') {
            current_token[i] = ' ';
            // add the read token (content from current_token) to the token list
            token_list[num_token] = read_token(current_token, strlen(current_token));
            num_token++;
            // reset the current_token array
            memset(current_token, 0, file_len  + 1);
        } else {
            current_token[i] = file_contents[i];
        }
        i++;
    }

    // check if the current_token is not empty and if so, add its content as the last token.
    if (strlen(current_token) > 0) {
        token_list[num_token] = read_token(current_token, strlen(current_token));
        num_token++;
    }

    free(current_token);
}