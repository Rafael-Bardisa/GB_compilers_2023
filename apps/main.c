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

    join(outfile, infile, "scn");

    FMT(RED, BLUE, YELLOW_BG);

    Automata keywords = load_automata("resources/keywords.txt");
    automata_info(keywords);

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
    scan_file(&lexer, infile, outfile);
    printf("\n\nThe number of operations is: %i. \n", opcount(&lexer));

    return 0;
}
