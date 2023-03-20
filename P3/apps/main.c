//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#include "main.h"
#include "parser.h"
#include "automata_sr.h"

Option_int test(){
    Option_int result = {
            .ok = TRUE,
            .value = 3,
    };
    return result;
}

int main(int argc, char **argv){

    char* infile = argv[1];
    /*
    Stack_Token token_test = Stack_Token_create(5);

    char* test_s = "<\"hello, world!\", CAT_LITERAL>";
    printf("%i", ' ' == ' ');

    Token test3 = read_token(test_s, strlen(test_s));

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

    Token cscn_file[22] = {0};


    //size_t file_size_num = file_size(open_file.value);

    char* contents = "<, CAT_NUMBER>  ";

    //fread(contents, sizeof (char),file_size_num, open_file.value);

    parse_str_to_tokens(contents, 16, cscn_file);

     //TODO ITERAR SOBRE TOKEN STACK
    for(int i = 0; i < token_test.stack.size; i++){
        int offset = i * sizeof(Token);
        Token* token_reference = (Token*) &token_test.stack.contents[offset];
        TKPRINT(token_reference);
    }
    printf("%s\n", FMT(BLUE_B));

    printf("%s", FMT(BLUE_BG));
    for (int i = 0; i < 1; i++){
        TKPRINT(&cscn_file[i]);
    }
    printf("%s\n", FMT(CLEAR));

    for (int i = 0; i < 5; i++){
        Token to_print = Stack_Token_pop(&token_test).value;
        TKPRINT(&to_print);
    }
     */
    //Parser parse

    /*Result_file file = file_open(infile, "r");

    if (file.status != OK) return -1;

    FILE* file_pointer = file.value;

    size_t fsize = file_size(file_pointer);

    char file_contents[fsize];
    Token token_list[64];

    fread(file_contents, sizeof(char), fsize, file_pointer);

    parse_str_to_tokens(file_contents, fsize, token_list);*/



    /* Production Rules
    1: S->E;
    2: E->T;
    3: E->E+T;
    4: T->T*F;
    5: T->F;
    6: F->NUM;
    7: F->(E);
    */
    /*
    size_t stack_size = 50;
    Stack_Token test_stack = Stack_Token_create(stack_size);
    Token A = create_token((char *) 'S', CAT_REDUCTION);
    for(int i = 0; i < stack_size; ++i){
        Token current_token = ; //get current_token
        int current_rule = ; //get value in rules
        // if in the current state it is possible to perform a reduction the value in rules[state][token] is not 0
        if(current_rule != 0){
            if (current_rule == 1){
                A.lexeme = (char *) 'S';
            }
            else if(current_rule == 2 || current_rule == 3){
                A.lexeme = (char *) 'E';
            }
            else if(current_rule == 4 || current_rule == 5){
                A.lexeme = (char *) 'T';
            }
            else if(current_rule == 6 || current_rule == 7){
                A.lexeme = (char *) 'F';
            }
            reduce(current_token, A, &test_stack);
        }
        // if no reduction can be applied (that is rules[state][token] = 0), perform a shift
        else {
            current_token = get_next_token;
            shift(current_token, &test_stack);
        }
    }
     */
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