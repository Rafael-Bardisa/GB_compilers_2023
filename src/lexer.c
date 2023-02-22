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
    //TODO may not work 100%
    //relative content index
    int content_idx = 0;
    bool accepted_token;
    int num_line = 1; // var to store the line #
    int elem_inline = 0; // var to check if its the first element (so we write the line # )

    int read_chars[lexer->num_automatas];
    //this loop will iterate through all characters in contents. Comparison done internally by the automatas
    // two main parts for algorithm: if any automata finds token and if none do
    while (content_idx != contents_len){
        if (*contents == ' '){
            content_idx++;
            contents++;
            continue;
        }
        // all automatas scan contents until either they identify a valid token or they get stuck
        // breaks early if a token is valid
        for(int i = 0; i < lexer->num_automatas; i++){
            accepted_token = FALSE;
            //get automata from lexer and initialize it
            Automata* current = &lexer->automatas[i];
            //done implicitly in scan function
            //start_automata(current);

            // store number of read characters in array
            int current_read = scan(current, contents, contents_len - content_idx);
            read_chars[i] = current_read;

            // read the token from the automata
            Token read_token = get_token(current);

            // if the token is valid, we assume no other automatas can parse a token from contents
            if(read_token.category != CAT_NONRECOGNIZED){
                //store the token in outfile
                accepted_token = TRUE;

                if(elem_inline == 0){
                    fprintf(outfile, "%i. ", num_line);
                }
                print_token(&read_token, outfile);
                elem_inline++;

                //advance the contents pointer for next iterations
                content_idx += current_read;
                contents += current_read;

                //break for loop, we don't need to check remaining automatas
                break;
            }
        }
        // if token was not accepted, find the smallest unrecognized token and advance contents pointer
        if (!accepted_token){
            //very big number
            int min_read_chars = 1 << 30;
            int min_read_chars_idx;
            for(int i = 0; i < lexer->num_automatas; i++){
                if (read_chars[i] < min_read_chars){
                    min_read_chars = read_chars[i];
                    min_read_chars_idx = i;
                }
            }
            //get the smallest unrecognized token and print it
            Token bad_token = get_token(&lexer->automatas[min_read_chars_idx]);

            //advance the contents pointer for next iterations
            content_idx += min_read_chars;
            contents += min_read_chars;

            //quick fix for newline
            if (*bad_token.lexeme == '\n') {
                num_line++;
                elem_inline = 0;
                fprintf(outfile, "\n");

            }

            // this else is for any other unrecognized symbols
            else{
                if(elem_inline == 0){
                    fprintf(outfile, "%i. ", num_line);
                }
                print_token(&bad_token, outfile);
                elem_inline++;
            }
        }

    }
    return 0;
}

int scan_file(Lexer* lexer, char* infile){
    FILE* input_file = fopen(infile, "r");
    int file_len = file_size(input_file);
    char* outfile = add_scn(infile);
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