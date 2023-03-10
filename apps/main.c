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
