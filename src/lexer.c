//
// Created by Rafael Bardisa Rodes on 31/1/23.
//
#include "lexer.h"

Lexer create_lexer(char** automata_files, int num_files){
    //TODO error handling
    Lexer new = {
            .automatas = malloc(num_files * sizeof (Automata)),
            .num_automatas = num_files,
    };
    for(int i = 0; i < num_files; i++){
        new.automatas[i] = load_automata(automata_files[i]);
    }

    return new;
}

void free_lexer(Lexer* lexer){
    //free each automata and then free allocated memory for automatas
    for(int i = 0; i < lexer->num_automatas; i++){
        free_automata(&lexer->automatas[i]);
    }
    free(lexer->automatas);
}

int scan_str(Lexer* lexer, char* contents, int contents_len, FILE* outfile){
    //TODO
    return -1;
}

int scan_file(Lexer* lexer, char* infile, char* outfile){
    FILE* input_file = fopen(infile, "r");
    int file_len = file_size(input_file);
    //TODO +1?
    char buffer[file_len];
    fread(buffer, file_len, 1, input_file);
    fclose(input_file);

    //if outfile is an empty string ("") redirect output to stdout
    bool outfile_defined = *outfile != '\0';

    FILE* output_file = outfile_defined ? fopen(outfile, "w+") : stdout;

    int return_status = scan_str(lexer, buffer, file_len, output_file);
    // do not close if file* is stdout
    if(outfile_defined) fclose(output_file);
    return return_status;
}

int opcount(Lexer* lexer){
    int res = 0;

    for (int i = 0; i < lexer->num_automatas; i++){
        res += lexer->automatas[i].countop;
    }
    return res;
}