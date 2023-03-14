//
// Created by Rafael Bardisa Rodes on 12/3/23.
//
#
#include "automata_sr.h"
Automata_SR create_automata(int num_states, Token* accepted_tokens, int num_accepted_states, const int* accepted_states, Category token_type){
    //know length of automata accepted characters for malloc
    int num_tokens = sizeof(accepted_tokens) / sizeof(Token);


    //initialize state matrix to 0 (i.e, all states point to not accepting state)
    int** states = calloc(num_states, sizeof (int*));
    for (int i = 0; i < num_states; i++){
        states[i] = calloc(num_tokens, sizeof(int));
    }

    //local alphabet_tokens for automata allows it to reference cells independently of outside alphabet_tokens
    Token* alphabet_tokens = calloc(num_tokens, sizeof(Token));
    memcpy(alphabet_tokens, accepted_tokens, sizeof(Token) * num_tokens);

    //allocate heap memory and copy accepted states there
    int* accepted_states_heap = calloc(num_accepted_states, sizeof(int));

    for (int i = 0; i < num_accepted_states; i++){
        accepted_states_heap[i] = accepted_states[i];
    }

    //create and return an automata
    Automata_SR automata = {
            .state_matrix = states,
            //.goto_matrix = goTo,

            .current_state = 0,  //which state the automata is currently at.

            .at = NULL,    //unused

            .accepted_tokens
            size_t num_accepted_tokens; // number of columns in automata

            int num_states; // number of states in the DFA

            int num_accepting_states;
            int* accepting_states;


            .state_matrix = states,
            .num_states = num_states,

            //TODO black magic
            .at = NULL,

            .accepted_tokens = alphabet_tokens,

            .current_state = 0,

            .num_accepting_states = num_accepted_states,
            .accepting_states = accepted_states_heap,
    };

    return automata;
}
