//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#include "main.h"



int main(int argc, char **argv){

    FILE * file = fopen(argv[1], "r");
    char character;
    char lexeme[255];
    int i = 0;
    Token tokens[sizeof(file)];

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
        if(character != ' '){
            character = fgetc(file);
            lexeme[i] = character;
            i++;
            Token token = get_token(lexeme, automata_arr );
            current_cat = token.category;
            if(prev_cat == current_cat ){

            }
        }

    } while (character != feof);



    /*  Automata test = create_automata(3, "abcdef", CAT_LITERAL);

    int** matrix = test.state_matrix;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 6; j++){
            printf("%s%i",FMT(BOLD, ITALICS, DASH) ,matrix[i][j]);
        }
    }

    printf("%s%i%s\n", FMT(WHITE_BG, BLACK), index_of(&test, 'a'), FMT(CLEAR));
    save_automata(&test, "test.txt");
    free_automata(&test);
    */

    //TODO relative paths, sync both CMake and Makefile builds

    Token scan_result = get_token("aa", automata_arr);
    TKPRINT(&scan_result);

    //automata_info();

}
