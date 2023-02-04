//
// Created by Rafael Bardisa Rodes on 3/2/23.
//

#ifndef COMPILERS_PROJECT_GB_AUTOMATA_H
#define COMPILERS_PROJECT_GB_AUTOMATA_H

#include <stdlib.h>

#include "common.h"
#include "tokens.h"

#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ{}()[]+<>*=;,\"0123456789"

/**
 * shorthand for print_automata
 */
#define automata_info(automata) print_automata(&(automata), getName(automata))

/**
 * struct to conveniently store an automata
 */
typedef struct automatus{
    Category token_type;

    int** state_matrix;
    int current_state;

    int* at;

    char* alphabet;

    // number of columns in automata
    int num_chars;
    //number of states in the DFA
    int num_states;
} Automata;

/**
 * Creates an automata with a given number of states and a list of all possible accepting characters. Automata is not started on creation
 * @param num_states how many states does the automata have
 * @param accepted_chars the complete list of characters for which there exists at least one valid state change (not to state 0)
 * @return
 */
Automata create_automata(int num_states, char* accepted_chars, Category token_type);

/**
 * Frees all calloced memory from the automata parameter
 * @param automata which automata to free memory from
 */
void free_automata(Automata* automata);

/**
 * Saves the automata to a file, where it is easier to modify and stored for later use
 * @param automata
 * @param file_path
 * @return
 */
int save_automata(Automata* automata, char* file_path);

/**
 * loads an automata from a file. Will assume the file is a valid automata file
 * @param file_path
 * @return
 */
Automata load_automata(char* file_path);

/**
 * Sets the automata's current state to 1 (i.e, the initial state). 0 is reserved for not accepted
 * @param automata
 */
void start_automata(Automata* automata);

/**
 * Auxiliary function that returns column index of letter in the automata.\n
 * If letter is not in the automata's alphabet, returns the wildcard index
 * @param automata
 * @param letter
 * @return
 */
int index_of(Automata* automata, char letter);

/**
 * Advances an automata to the next state in its DFA, represented internally by its state matrix
 * @param automata which automata to run
 * @param letter which letter has been read
 * @return which state the automata is in. 0 is an invalid state
 */
int advance(Automata* automata, char letter);

/**
 * Runs the automata on a given lexeme. Returns a token if accepted
 * @param automata
 * @param lexeme
 * @returns Token{0} if not in the accepting state, else Token{lexeme, automata.token_type}
 */
Token scan(Automata* automata, char* lexeme);

/**
 * Prints the infotmation held in the automata
 * @param automata
 */
void print_automata(Automata* automata, char* automata_name);

#endif //COMPILERS_PROJECT_GB_AUTOMATA_H
