//
// Created by Rafael Bardisa Rodes on 3/2/23.
//

#ifndef COMPILERS_PROJECT_GB_AUTOMATA_SR_H
#define COMPILERS_PROJECT_GB_AUTOMATA_SR_H

#include <stdlib.h>

#include "common.h"
#include "result.h"
#include "tokens.h"

//up to 1 Mb files
#define SR_MAX_FILE_SIZE (1024 * 1024)
#define SR_MAX_TOKEN_LEN 64

/*
typedef struct rule{
    1: S->E;
    2: E->T;
    3: E->E+T;
    4: T->T*F;
    5: T->F;
    6: F->NUM;
    7: F->(E);
}; */

/*
typedef struct cell{
    int next_state;
    Action action;
} Cell;
*/

/*
typedef struct rule {
    Token original;
    Token* substitution;
} Rule;
*/
/**
 * struct to store a shift-reduce automata
 */
typedef struct automata_sr{
    int** state_matrix; //matrix representation of the automata's associated DFA.
    int** goto_matrix;
    int** rules_matrix;

    int current_state;  //which state the automata is currently at.

    int* at;    //unused

    Token* accepted_tokens; //list of tokens that define transitions in the automata.
                            // Internally, there is an extra "wildcard" character for tokens not in the list.
    Token* accepted_goto; //list of tokens that define transitions in the automata.
                         // Internally, there is an extra "wildcard" character for tokens not in the list.

    size_t num_accepted_tokens; // number of columns in automata

    int num_states; // number of states in the DFA
    int num_goto; // number of states in the goto DFA

    int num_accepting_states;
    int* accepting_states;
} Automata_SR;

/**
 * Creates a shift reduce automata with a given number of states and a list of all possible accepting tokens. Automata is not started on creation
 * @param num_states how many states does the automata have
 * @param accepted_chars the complete list of tokens for which there exists at least one valid state change (not to state 0)
 * @param num_accepted_states the length of the array of accepted states
 * @param accepted_states array of accepted states (ints)
 * @return
 */
Automata_SR create_automata_sr(int num_states, Token* accepted_tokens, int num_accepted_states, const int* accepted_states, int num_goto, Token* accepted_goto);

/**
 * Frees all calloced memory from the shift reduce automata parameter
 * @param automata which automata to free memory from
 */
void Automata_SR_free(Automata_SR* automata);

/**
 * Saves the automata to a file, where it is easier to modify and stored for later use
 * @param automata
 * @param file_path
 * @return
 */
int Automata_SR_save(Automata_SR* automata, const char* file_path);

/**
 * loads an automata from a file. Will assume the file is a valid automata file
 * @param file_path
 * @return
 */
Automata_SR Automata_SR_load(char* goto_path, char* rules_path, char* states_path);

/**
 * Sets the automata's current state to 1 (i.e, the initial state). 0 is reserved for not accepted
 * @param automata
 */
void Automata_SR_start(Automata_SR* automata);

/**
 * Auxiliary function that returns column index of letter in the automata.\n
 * If letter is not in the automata's alphabet, returns the wildcard index
 * @param automata
 * @param letter
 * @return
 */
int _SR_index_of(Automata_SR* automata, Token token);

/**
 * returns automata matrix[state][token]
 * @param automata
 * @param token
 * @return
 */
int _SR_peek(Automata_SR* automata, Token token);

/**
 * Advances an automata to the next state in its DFA, represented internally by its state matrix
 * @param automata which automata to run
 * @param letter which letter has been read
 * @return which state the automata is in. 0 is an invalid state
 */
int _SR_advance(Automata_SR* automata, Token token);

/**
 * Runs the automata on a given expression. Returns whether it is a valid expression on the automata's grammar
 * @param automata
 * @param lexeme
 * @returns the number of characters read from lexeme
 */
int Automata_SR_parse(Automata_SR* automata, Token* expression, int expression_len);

/**
 * Prints the infotmation held in the automata
 * @param automata
 * @param lexeme
 * @param lexeme_len the length of the lexeme string
 * @return the number of characters read from lexeme
 */
void print_automata_SR(Automata_SR* automata, char* automata_name);

/**
 * abstraction of automata.current_state == 0.
 * @param automata
 * @return true if automata.current state is 0 (i.e, the automata is stuck), else false
 */
bool _stuck_SR(Automata_SR* automata);

/**
 * abstraction of automata.current_state == num_states - 1
 * @param automata
 * @return true if automata.current_state is last state (i.e, automata is in accepting state), else false
 */
bool _accept_SR(Automata_SR* automata);

/**
 *  performs the reduction A -> β
 * @param beta sybmols on stack match β for some A -> β
 * @param A non-terminal variable
 * @param stack
 */
void reduce(Token current_token, Token A, Stack_Token* stack);

/**
 *
 * @param token
 * @param stack
 */
void shift(Token token, Stack_Token* stack);

Automata_SR load_automata(char* file_path);

#endif //COMPILERS_PROJECT_GB_AUTOMATA_SR_H