//
// Created by Rafael Bardisa Rodes on 12/3/23.
//

#include "parser.h"
#include "tokens.h"

Parser Parser_new(char* token_file, char* goto_file, char* rules_file, char* states_file){

    Parser result = {
            .stack = Stack_Token_create(PARSER_CAPACITY),
            .file_as_tokens = calloc(PARSER_CAPACITY, sizeof (Token)),
            .automata = Automata_SR_load(goto_file, rules_file, states_file),
    };
    parse_file_to_tokens(token_file, result.file_as_tokens);
}

void parse(Parser* parser, const char* filename){

}

size_t num_tokens_in_string(const char* string){

}


Token* str_to_tokens(const char* string){

}


int parse_file_to_tokens(char* filename, Token* token_list){
    Result_file file = file_open(filename, "r");
    if (file.status != OK) return -1;

    FILE* file_pointer = file.value;

    size_t fsize = file_size(file_pointer);

    char file_contents[fsize];

    fread(file_contents, sizeof(char), fsize, file_pointer);

    return parse_str_to_tokens(file_contents, fsize, token_list);
}