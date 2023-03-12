//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#include "main.h"

Option_int test(){
    Option_int result = {
            .ok = TRUE,
            .value = 3,
    };
    return result;
}

int main(int argc, char **argv){

    char* infile = argv[1];

    Stack_Token token_test = Stack_Token_create(5);

    Token test1 = {
            .lexeme = "world!",
            .category = CAT_IDENTIFIER,
    };
    Token test2 = {
            .lexeme = "Hello",
            .category = CAT_NUMBER,
    };


    Stack_Token_push(&token_test, test1);
    Stack_Token_push(&token_test, test2);
    Stack_Token_push(&token_test, test2);
    Stack_Token_push(&token_test, test1);
    Stack_Token_push(&token_test, test2);

    for (int i = 0; i < 5; i++){
        Token to_print = Stack_Token_pop(&token_test).value;
        TKPRINT(&to_print);
    }

    //must initialize as list of char*
    char* files[7] = {
            "resources/literals.txt",
            "resources/numbers.txt",
            "resources/identifier.txt",
            "resources/special_char.txt",
            "resources/types.txt",
            "resources/operators.txt",
            "resources/keywords.txt",
    };


    Automata test = load_automata(files[6]);
    print_automata(&test, "nombre");


    Lexer lexer = create_lexer(files, 7);


    if(infile == NULL){
        printf("\nError 0: No file present, check man page.\n");
    }
    else{
        join(outfile, infile, "scn");
        scan_file(&lexer, infile, outfile);
        printf("\n\nThe number of operations is: %i. \n", opcount(&lexer));
    }

    return 0;
}
