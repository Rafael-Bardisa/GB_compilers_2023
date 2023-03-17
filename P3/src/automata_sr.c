//
// Created by Rafael Bardisa Rodes on 12/3/23.
//

#include "automata_sr.h"
#include "tokens.h"
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

            .accepted_states = alphabet_states,
            .accepted_goto = alphabet_goto,

            .num_states = num_states,
            .num_goto = num_goto,


            .num_accepting_states = num_accepted_states,
            .accepting_states = accepted_states_heap,
    };

    return automata;
}

void Automata_SR_free(Automata_SR *automata) {
    free(automata->accepted_states);
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




