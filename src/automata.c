//
// Created by Rafael Bardisa Rodes on 3/2/23.
//

#include "automata.h"

Automata create_automata(int num_states, char* accepted_chars, int num_accepted_states, const int* accepted_states, Category token_type){
    //know length of automata accepted characters for malloc
    int num_chars = strlen(accepted_chars) + 1;

    //initialize state matrix to 0 (i.e, all states point to not accepting state)
    int** states = calloc(num_states, sizeof (int*));
    for (int i = 0; i < num_states; i++){
        // extra column to specify wildcard characters (any character not specified as accepted)
        // can be used for literal matching
        states[i] = calloc(num_chars, sizeof(int));
    }

    //local alphabet for automata allows it to reference cells independently of outside alphabet
    char* alphabet = calloc(num_chars, sizeof(char));
    strcpy(alphabet, accepted_chars);

    //allocate heap memory and copy accepted states there
    int* accepted_states_heap = calloc(num_accepted_states, sizeof(int));

    for (int i = 0; i < num_accepted_states; i++){
        accepted_states_heap[i] = accepted_states[i];
    }

    //create and return an automata
    Automata automata = {
            .token_type = token_type,
            //TODO malloc returns an allocated pointer so it is not null but it must take into account possible overflows
            .scanned = malloc(DEFAULT_LEXEME_LENGTH * sizeof(char)),
            .lexeme_capacity = DEFAULT_LEXEME_LENGTH,

            .state_matrix = states,
            .num_states = num_states,

            //TODO black magic
            .at = NULL,

            .alphabet = alphabet,
            .num_chars = num_chars,

            .current_state = 0,
            .countop = 0,

            .num_accepting_states = num_accepted_states,
            .accepting_states = accepted_states_heap,
    };

    return automata;
}

void free_automata(Automata* automata){
    //reverse process as create_automata, much faster because only need to free calloced memory
    free(automata->alphabet);
    for (int i = 0; i < automata->num_states; i++){
        free(automata->state_matrix[i]);
    }
    free(automata->state_matrix);
    free(automata->scanned);
    free(automata->accepting_states);
}

int save_automata(Automata* automata, char* file_path){
    // some information is not needed to save, this is the minimum necessary to make the automata work
    // default values can be (and are) set easy from code (i.e, default lexeme length)

    //use custom result type to check for errors when opening file
    Result_file open_file = file_open(file_path, "w+");

    if (open_file.status != OK){
        explain_error(open_file);
    }

    FILE* save_file = open_file.value;

    // information header for later correct retrieval of the automata
    fprintf(save_file, "%i %s %s %i\n", automata->num_states, automata->alphabet, cat_to_str(&automata->token_type), automata->num_accepting_states);

    int first_char = TRUE;

    for(int i = 0; i < automata->num_accepting_states; i++){
        if (!first_char) fprintf(save_file, " ");
        fprintf(save_file, "%i", automata->accepting_states[i]);
        first_char = FALSE;
    }
    fprintf(save_file, "\n");

    for(int i = 0; i < automata->num_states; i++){
        first_char = TRUE;
        for(int j = 0; j < automata->num_chars; j++){
            if (!first_char) fprintf(save_file, " ");
            fprintf(save_file, "%i", automata->state_matrix[i][j]);
            first_char = FALSE;
        }
        fprintf(save_file, "\n");
    }

    fclose(save_file);
    return 0;
}

Automata load_automata(char* file_path){

    //use custom result type to check for errors when opening file
    Result_file open_file = file_open(file_path, "r");

    if (open_file.status != OK){
        explain_error(open_file);
    }

    FILE *save_file = open_file.value;

    int num_states;
    int num_accepting_states;
    //preemptively allocate enough space for reading the buffer
    // assumes neither alphabet or category are larger than specified. If working with ascii, they should suffice
    char alphabet[512];
    char category[128];

    fscanf(save_file, "%i %s %s %i", &num_states, alphabet, category, &num_accepting_states);

    int accepting_states[num_accepting_states];
    for (int i = 0; i < num_accepting_states; i++){
        fscanf(save_file, "%i", &accepting_states[i]);
    }

    Automata automata = create_automata(num_states, alphabet,  num_accepting_states, accepting_states, str_to_cat(category));

    for (int i = 0; i < automata.num_states; i++){
        for (int j = 0; j < automata.num_chars; j++){
            fscanf(save_file, "%i", &automata.state_matrix[i][j]);
        }
    }

    fclose(save_file);
    return automata;
}

void start_automata(Automata* automata){
    automata->current_state = 1;
}

int index_of(Automata* automata, char letter){
    // crawl over the automata alphabet and return the index if letter matches
    for(int i = 0; i < automata->num_chars - 1; i++){
        //is a comparison operation
        automata->countop++;
        if(automata->alphabet[i] == letter) return i;
    }
    // letter is not in the alphabet, return wildcard column
    return automata->num_chars - 1;
}

int peek(Automata* automata, char letter){
    int letter_idx = index_of(automata, letter);
    return automata->state_matrix[automata->current_state][letter_idx];
}

int advance(Automata* automata, char letter){
    automata->current_state = peek(automata, letter);

    return automata->current_state;
}

int scan(Automata* automata, char* lexeme, int lexeme_len){
    // set automata current index to 1
    start_automata(automata);
    //this can and should be passed as parameter for less computations
    //int lexeme_len = strlen(lexeme);

    // iterate over lexeme, advance automata current state according to its DFA
    for (int i=0; i < lexeme_len; i++){
        // advance to next automata state. Modifies automata current state
        advance(automata, lexeme[i]);
        //TODO realloc if i+1 > automata lexeme capacity

        // token is not recognized if the automata is stuck or recognized if it is accepted and next character would not be.
        if (stuck(automata) || (accept(automata) && !peek(automata, lexeme[i+1]))) {
            //comparison determines lexeme has a token. Store it in the automata struct and return number of characters read
            //strncpy is not used for comparison because we already know what the token is (lexeme[0:i])
            strncpy(automata->scanned, lexeme, i+1);
            automata->scanned[i+1] = '\0';
            return i + 1;
        }
    }
    // read all characters in lexeme
    strncpy(automata->scanned, lexeme, lexeme_len);
    return lexeme_len;
    /*
    //if automata did not reach accepting state after crawling lexeme return null token
    if(automata->current_state != automata->num_states - 1){
        Token token = {0};
        return 0;


    }
     */
    // lexeme is accepted, return a token
    Token token = {.lexeme = lexeme, .category = automata->token_type};
    return 0;
}

void print_automata(Automata* automata, char* automata_name){
    int alphabet_len = strlen(automata->alphabet);
    char alphabet[alphabet_len];
    strcpy(alphabet, automata->alphabet);

    printf("\n%s<%s> information:\n\n", FMT(BLUE_B, BOLD), automata_name);

    printf("%sNumber of states:%s\t%i\n", FMT(CLEAR), FMT(BLUE_B), automata->num_states);
    printf("%sAllowed characters:%s\t%s%s + %swildcard\n",FMT(CLEAR), FMT(BLUE_B), alphabet, FMT(CLEAR), FMT(MAGENTA));
    printf("%sLexeme reserved space (bytes):%s\t%i%s\n",FMT(CLEAR), FMT(BLUE_B), automata->lexeme_capacity, FMT(CLEAR));
    printf("%sToken type:%s\t%s\n",FMT(CLEAR), FMT(BLUE_B), cat_to_str(&automata->token_type));

    printf("%sAccepting states:\t[",FMT(CLEAR));

    bool first = TRUE;
    for(int i = 0; i < automata->num_accepting_states; i++){
        if(!first) printf("%s, ",FMT(CLEAR));
        printf("%sq%i", FMT(YELLOW_B), automata->accepting_states[i]);
        first = FALSE;
    }
    printf("%s]\n\n", FMT(CLEAR));

    printf("%sDFA matrix representation:\n\n\t", FMT(BLUE_B));

    foreach(char* letter in alphabet){
        printf("%c\t", *letter);
    }
    printf("%s%s\n", FMT(MAGENTA), SIGMA);

    for(int i = 0; i < automata->num_states; i++){
        char* q_fmt = i == automata->num_states - 1 ? FMT(YELLOW_B) : FMT(BLUE_B);

        printf("%sq%i\t", q_fmt, i);
        for(int j = 0; j < automata->num_chars; j++){
            //pretty printing info
            int next_state = automata->state_matrix[i][j];
            char* fmt = next_state ? isin_int(automata->accepting_states, automata->num_accepting_states, automata->current_state) ? FMT(YELLOW_B) : j == automata->num_chars - 1 ? FMT(MAGENTA) : FMT(BLUE_B) : FMT(GRAY);

            printf("%s%i\t", fmt, next_state);
        }
        printf("\n");
    }
}

//TODO review
Token get_token(Automata* automata){
    // if automata is not in accepting state, it did not recognize the lexeme
    Category category = accept(automata) ? automata->token_type : CAT_NONRECOGNIZED;

    // easy to understand if written like this
    Token value = {
            .lexeme = automata->scanned,
            .category = category,
    };

    return value;
}
/*
Token get_token(char* lexeme, Automata automatas[]){
    // keywords
    if(scan(&automatas[0], lexeme).category == CAT_KEYWORD){
        return create_token(lexeme, CAT_KEYWORD);
    }
        // identifiers
    else if(scan(&automatas[1], lexeme).category == CAT_IDENTIFIER){
        return create_token(lexeme, CAT_IDENTIFIER);
    }
        // literals
    else if(scan(&automatas[2], lexeme).category == CAT_LITERAL){
        return create_token(lexeme, CAT_LITERAL);
    }
        // types
    else if(scan(&automatas[3], lexeme).category == CAT_TYPE){
        return create_token(lexeme, CAT_TYPE);
    }
        // special characters
    else if(scan(&automatas[4], lexeme).category == CAT_SPECIALCHAR){
        return create_token(lexeme, CAT_SPECIALCHAR);
    }// operators
    else if(scan(&automatas[5], lexeme).category == CAT_OPERAND){
        return create_token(lexeme, CAT_OPERAND);
    }
        // numbers
    else if(scan(&automatas[6], lexeme).category == CAT_NUMBER){
        return create_token(lexeme, CAT_NUMBER);
    }
    else{
        return create_token(lexeme, CAT_NONRECOGNIZED);
    }

}

#define USE_ISIN(type) bool isin_##type(type *container, size_t container_size, type element) {\
for (int i = 0; i < container_size; i++) {\
if (container[i] == element) { return 1; }\
}\
return 0;\
}


USE_ISIN(char)

*/

bool stuck(Automata* automata){
    return (automata->current_state == 0);
}

bool accept(Automata* automata){
    return isin_int(automata->accepting_states, automata->num_accepting_states, automata->current_state);
}