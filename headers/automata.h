//
// Created by Rafael Bardisa Rodes on 3/2/23.
//

#ifndef COMPILERS_PROJECT_GB_AUTOMATA_H
#define COMPILERS_PROJECT_GB_AUTOMATA_H

#include <stdlib.h>

#include "common.h"
#include "tokens.h"

#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ{}()[]+<>*=;,\"0123456789"
#define DEFAULT_LEXEME_LENGTH 128

/**
 * shorthand for print_automata
 */
#define automata_info(automata) print_automata(&(automata), getName(automata))

/**
 * struct to conveniently store an automata
 */
typedef struct automata{
    //does not directly store token but is easy to retrieve
    Category token_type;    //which type of token is the automata supposed to scan
    char* scanned;  //char buffer to store read characters from a string. Not realloced because it's been given reasonable capacity

    int lexeme_capacity;    //capacity of scanned buffer. Dynamic change is not implemented, all tokens should be at most this length

    int** state_matrix; //matrix representation of the automata's associated DFA. Current implementation allows for only ONE accepting state.
    int current_state;  //which state the automata is currently at.

    int* at;    //unused

    char* alphabet;//list of characters that define transitions in the automata. Internally, there is an extra "wildcard" character for characters not in the list.


    int num_chars;  // number of columns in automata

    int num_states; // number of states in the DFA

    int countop;    // number of comparison operations, should be equal to sum of all indexof
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
 * returns automata matrix[state][letter]
 * @param automata
 * @param letter
 * @return
 */
int peek(Automata* automata, char letter);

/**
 * Advances an automata to the next state in its DFA, represented internally by its state matrix
 * @param automata which automata to run
 * @param letter which letter has been read
 * @return which state the automata is in. 0 is an invalid state
 */
int advance(Automata* automata, char letter);

/**
 * Runs the automata on a given lexeme. Returns the number of characters read
 * @param automata
 * @param lexeme
 * @returns the number of characters read from lexeme
 */
int scan(Automata* automata, char* lexeme, int lexeme_len);

/**
 * Prints the infotmation held in the automata
 * @param automata
 * @param lexeme
 * @param lexeme_len the length of the lexeme string
 * @return the number of characters read from lexeme
 */
void print_automata(Automata* automata, char* automata_name);

/**
 * returns the token read by the automata. Handles automata state internally
 * @param automata
 * @return Token{automata.lexeme, category}
 */
Token get_token(Automata* automata);

/**
 * abstraction of automata.current_state == 0.
 * @param automata
 * @return true if automata.current state is 0 (i.e, the automata is stuck), else false
 */
bool stuck(Automata* automata);

/**
 * abstraction of automata.current_state == num_states - 1
 * @param automata
 * @return true if automata.current_state is last state (i.e, automata is in accepting state), else false
 */
bool accept(Automata* automata);

#endif //COMPILERS_PROJECT_GB_AUTOMATA_H