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

    char* strtest = "";

    Option_int int_test = test();
    if (!int_test.ok) return -1;
    FILE * file = fopen("", "r");
    int result_value = int_test.value;
    printf("%s%i%s\n", FMT(MAGENTA, WHITE_BG), result_value, FMT(CLEAR));

    bool test2 = FALSE;
    char* test = "hello, world";
    printf("%lu: %s\n", strlen(test), test);
    test += 5;  //move test pointer 5 chars in memory (sizeof char
    if(test2) {
        printf("%i: %s", strlen(test), test);
    }
    Automata keywords = load_automata("resources/keywords.txt");
    automata_info(keywords);

    printf("%i",scan(&keywords, "_234", 11));
    Token token = get_token(&keywords);
    TKPRINT(&token);
    printf("%i", *strtest ? 1 : 0);

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
    Lexer lexer = create_lexer(files, 7);

    printf("\n%s", FMT(CLEAR));
    //scan_str(&lexer, "1234_43\"hhhh\"8937213soyIdentifier", 33, stdout);
    scan_file(&lexer, "resources/my_test.c", "");

    printf("\n%i", opcount(&lexer));

    return 0;
/*
    FILE * file = fopen(argv[1], "r");
    // char file_str[fileSize(file)];

    //read(file, fileSize(file), pointer);
    char character;
    char lexeme[255];
    int i = 0;
    Automata keywords = load_automata("keywords.txt");
    Automata numbers = load_automata("numbers.txt");
    Automata operators = load_automata("operators.txt");
    Automata literals = load_automata("literals.txt");
    Automata identifiers = load_automata("identifier.txt");
    Automata special_chars = load_automata("special_char.txt");
    Automata types = load_automata("types.txt");

    Automata automata_arr[] = {keywords, identifiers, literals, types, special_chars, operators, numbers};

    // Automata multiline = load_automata("multiline_comments.txt");

    Category current_cat;
    Category prev_cat = CAT_NULL;
    do{
        character = fgetc(file);
        //TODO: keywords followed by ()?...
        if(character != ' ') {
            character = fgetc(file);
            lexeme[i] = character;
            i++;
            Token token = get_token(lexeme, automata_arr );
            current_cat = token.category;
            if(prev_cat != current_cat && prev_cat == CAT_NONRECOGNIZED ){ //this for identifiers/types
                write
                prev_cat = current_cat;
            }
            else if(prev_cat != c)

        }

    } while (character != feof);


    //TODO relative paths, sync both CMake and Makefile builds

    Token scan_result = get_token("aa", automata_arr);
    TKPRINT(&scan_result);

    //automata_info();
     */

}
