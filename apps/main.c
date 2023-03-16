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

    char* test_s = "<\"hello, world!\", CAT_LITERAL>";
    printf("%i", ' ' == ' ');
    /*
    Token test3 = read_token(test_s, strlen(test_s));

    TKPRINT(&test3);
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
    }*/


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


    Automata test = load_automata(files[0]);
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

/**
* 3 + 45 + (64)
 * 3 !0
 * E !0
 * E + !0
 * E + 45 !0
 * E + E !0
 * NOT ACCEPTED
*/

/**
* 3 + (45 + (64)
 * 3 !0
 * E !0
 * E + !0
 * E + ( !0
 * E + (45 !0
 * E + (E !0
 * E + (E + !0
 * E + (E + ( !0
 * E + (E + (64 !0
 * E + (E + (E !0
 * E + (E + (E)
 * E + (E
 * E + (E$
 * NOT ACCEPTED
*/

/**
* 3 + (45 + (64)
 * 0
 * 1 E > int
 * 2
 * 3
 * 4
 * 5 E > int
 * 6
 * 8
 * 9
 * 5 E > int
 * 10?  |6
 * 11? E > E + (E)|7
 * 6 > not accept state
*/