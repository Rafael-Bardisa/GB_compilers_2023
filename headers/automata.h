//
// Created by Rafael Bardisa Rodes on 3/2/23.
//

#ifndef COMPILERS_PROJECT_GB_AUTOMATA_H
#define COMPILERS_PROJECT_GB_AUTOMATA_H

#include "common.h"
#include <stdlib.h>

#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ{}()[]+<>*=;,\"0123456789"

/**
 * struct to conveniently store an automata
 */
typedef struct _automata{
    int** state_matrix;
    int current_state;

    int* at;

    char* alphabet;

    int num_states;

} Automata;

/**
 * Creates an automata with a given number of states and a list of all possible accepting characters
 * @param num_states how many states does the automata have
 * @param accepted_chars the complete list of characters for which there exists at least one valid state change (not to state 0)
 * @return
 */
Automata create_automata(int num_states, char* accepted_chars);

/**
 * Frees all calloced memory from the automata parameter
 * @param automata which automata to free memory from
 */
void free_automata(Automata automata);

/**
 * Saves the automata to a file, where it is easier to modify and stored for later use
 * @param automata
 * @param file_path
 * @return
 */
int save_automata(Automata automata, char* file_path);

/**
 * loads an automata from a file. Will assume the file is a valid automata file
 * @param file_path
 * @return
 */
Automata load_automata(char* file_path);

/**TODO
 * Advances an automata to the next state in its DFA, represented internally by its state matrix
 * @param automata which automata to run
 * @param letter which letter has been read
 * @return which state the automata is in. 0 is an invalid state
 */
int advance(Automata automata, char letter);



#endif //COMPILERS_PROJECT_GB_AUTOMATA_H
