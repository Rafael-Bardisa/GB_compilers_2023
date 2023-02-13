//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#include "main.h"



int main(int argc, char **argv){

    char* strtest = "";

    bool test2 = FALSE;
    char* test = "hello, world";
    printf("%i: %s\n", strlen(test), test);
    test += 5;  //move test pointer 5 chars in memory (sizeof char
    if(test2) {
        printf("%i: %s", strlen(test), test);
    }
    Automata keywords = load_automata("resources/keywords.txt");
    automata_info(keywords);

    printf("%i",scan(&keywords, "whilekarlos", 11));
    Token token = get_token(&keywords);
    TKPRINT(&token);
    printf("%i", *strtest ? 1 : 0);
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
