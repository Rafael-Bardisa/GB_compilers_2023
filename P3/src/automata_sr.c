//
// Created by Rafael Bardisa Rodes on 12/3/23.
//

#include "automata_sr.h"

Automata_SR create_automata_sr(int num_states, Token* accepted_tokens, int num_accepted_states, const int* accepted_states, int num_goto, Token* accepted_goto){
    //know length of automata accepted characters for malloc
    int sizeof_acc = sizeof(*accepted_tokens);
    int sizeof_non = sizeof(*accepted_goto);
    int num_tokens = sizeof_acc / sizeof(Token);
    int num_non_tokens = sizeof_non / sizeof (Token);


    //initialize state matrix to 0 (i.e, all states point to not accepting state)
    int** states = calloc(num_states, sizeof (int*));
    int** goto_matrix = calloc(num_goto, sizeof (int*));
    int** rules_matrix = calloc(num_states, sizeof(int*));
    for (int i = 0; i < num_states; i++){
        states[i] = calloc(num_tokens, sizeof(int));
    }
    for(int i = 0; i < num_goto; i++){
        goto_matrix[i] = calloc(num_non_tokens, sizeof(int));
    }

    //local alphabet_states for automata allows it to reference cells independently of outside alphabet_states
    Token* alphabet_states = calloc(num_tokens, sizeof(Token));
    memcpy(alphabet_states, accepted_tokens, sizeof_acc);

    //local alphabet_states for automata allows it to reference cells independently of outside alphabet_states
    Token* alphabet_goto = calloc(num_non_tokens, sizeof(Token));
    memcpy(alphabet_goto, accepted_goto, sizeof_non);

    //allocate heap memory and copy accepted states there
    int* accepted_states_heap = calloc(num_accepted_states, sizeof(int));

    for (int i = 0; i < num_accepted_states; i++){
        accepted_states_heap[i] = accepted_states[i];
    }

    //create and return an automata
    Automata_SR automata = {
            .state_matrix = states,
            .goto_matrix = goto_matrix,

            .current_state = 0,  //which state the automata is currently at.

            .at = NULL,    //unused

            .accepted_tokens = alphabet_states,
            .accepted_goto = alphabet_goto,

            .num_states = num_states,
            .num_goto = num_goto,


            .num_accepting_states = num_accepted_states,
            .accepting_states = accepted_states_heap,
    };

    return automata;
}

void Automata_SR_free(Automata_SR *automata) {
    free(automata->accepted_tokens);
    free(automata->accepted_goto);
    for (int i = 0; i < automata->num_states ; ++i) {
        free(automata->state_matrix[i]);
    }
    free(automata->state_matrix);

    for (int i = 0; i < automata->num_goto ; ++i) {
        free(automata->goto_matrix[i]);
    }
    free(automata->goto_matrix);
    free(automata->accepting_states);
}

void Automata_SR_start(Automata_SR *automata) {
    automata->current_state = 1;
}

void reduce(char* beta, Token* A, Stack_Token* stack){
    size_t len_beta = strlen(beta);
    for(int i = 0; i < len_beta; ++i){
        Stack_Token_pop(stack);
    }
    Stack_Token_push(stack, *A);
}


void shift(Token* token, Stack_Token* stack){
    Stack_Token_push(stack, *token);
}

void load_goto(Automata_SR* automata, char* goto_path){
    //if goto matrix is already allocated, remove it
    if (automata->goto_matrix){
        for(int i = 0; i < automata->num_goto; i++){
            free(automata->goto_matrix[i]);
        }
        free(automata->goto_matrix);
    }
    Result_file goto_file_result = file_open(goto_path, "r");
    if(goto_file_result.status != OK){
        explain_error(goto_file_result);
    }
    FILE* goto_file = goto_file_result.value;
    //token alphabet of sr automata
    Token goto_tokens[SR_MAX_TOKEN_LEN];
    //temporary char array of tokens
    char token_header[SR_MAX_FILE_SIZE] = {0};

    fscanf(goto_file, "%i %s", &automata->num_goto, token_header);

    int num_tokens = parse_str_to_tokens(token_header, SR_MAX_FILE_SIZE, goto_tokens);
    automata->accepted_goto = goto_tokens;

    //allocate matrix pointer
    automata->goto_matrix = calloc(automata->num_goto, sizeof(int*));

    for (int i = 0; i < automata->num_goto; i++){
        //allocate each row pointer
        automata->goto_matrix[i] = calloc(num_tokens + 1, sizeof(int));
        for (int j = 0; j < automata->accepted_tokens; j++){
            //allocate each value
            fscanf(goto_file, "%i", &automata->goto_matrix[i][j]);
        }
    }
}
void load_rules(Automata_SR* automata, char* rules_path);
void load_states(Automata_SR* automata, char* states_path){
    //if state matrix is already allocated, remove it
    if (automata->state_matrix){
        for(int i = 0; i < automata->num_states; i++){
            free(automata->state_matrix[i]);
        }
        free(automata->state_matrix);
    }
    Result_file states_file_result = file_open(states_path, "r");
    if(states_file_result.status != OK){
        explain_error(states_file_result);
    }
    FILE* states_file = states_file_result.value;
    //token alphabet of sr automata
    Token state_tokens[SR_MAX_TOKEN_LEN];
    //temporary char array of tokens
    char token_header[SR_MAX_FILE_SIZE] = {0};

    fscanf(states_file, "%i %s %i", &automata->num_states, token_header, &automata->num_accepting_states);

    int num_tokens = parse_str_to_tokens(token_header, SR_MAX_FILE_SIZE, state_tokens);
    automata->accepted_tokens = state_tokens;

    //allocate matrix pointer
    automata->state_matrix = calloc(automata->num_states, sizeof(int*));

    for (int i = 0; i < automata->num_states; i++){
        //allocate each row pointer
        automata->state_matrix[i] = calloc(num_tokens + 1, sizeof(int));
        for (int j = 0; j < automata->accepted_tokens; j++){
            //allocate each value
            fscanf(states_file, "%i", &automata->state_matrix[i][j]);
        }
    }
}

/*TODO
Automata_SR Automata_SR_load(char* goto_path, char* rules_path, char* states_path){
    //use custom result type to check for errors when opening file

    return automata;
}
 */
