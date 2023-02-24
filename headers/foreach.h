//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

//TODO has little errors, only use when 100% sure it working to avoid unnecesarily difficult bugs
//also, unused

#ifndef COMPILERS_FOREACH_H
#define COMPILERS_FOREACH_H

#include <stdio.h>
#include <string.h>

/**
 * just a (
 */
#define LPAREN (
/**
 * just a )
 */
#define RPAREN )

/**
 * I have 0 clue what this one does but it is needed so don't touch please ;_;
 */
#define EXPAND(...) __VA_ARGS__

/**
 * Auxiliary macro that, given OP a macro, D a string like "\<type\> \<identifier\>",
 * and A an arbitrary identifier, expands to EXPAND(OP, SPLIT_\<type\> \<identifier\> COMMA A RPAREN)
 * \n\n
 * In conjunction with the helper macros below, it becomes:\n
 * EXPAND(OP LPAREN \<type\> COMMA \<identifier\> COMMA A RPAREN)\n\n
 * which must be equivalent to the following or else it wouldn't work i guess\n
 * OP(\<type\>, \<identifier\>, A)
 */
#define SPLIT(OP, D, A) EXPAND(OP SPLIT_##D in A RPAREN)

/**
 * magic macros for whatever the specified \<type\> was
 */
#define SPLIT_int LPAREN int in
#define SPLIT_char LPAREN char in
#define SPLIT_float LPAREN float in
#define SPLIT_double LPAREN double in
#define SPLIT_Token LPAREN Token in
#define SPLIT_Automata LPAREN Automata in

/**
 * for loop similar to python's "for elem in list" heavily encapsulated to provide an easy way to write it\n\n
 * uses tricky second for loop to encapsulate the normal index and directly retrieve array[i] into item
 */
#define FOREACH(type, item, array, size) \
    for (size_t X(keep) = 1, X(i) = 0; X(i) < (size); X(keep) = 1, X(i)++) \
    for (type item = &(array)[X(i)]; X(keep); X(keep) = 0)

#define foreach_(type, item, array) FOREACH(type, item, array, sizeof(array)/sizeof((array)[0]))
/**
 * foreach(\<type\> \<name\> in \<array\>) construct, probably the pinnacle of computer science in 1970\n
 * The second for loop is a lie, only used for natural bracket placement\n
 * Elements returned are addresses to the original array. Allows for array manipulation on top of normal reading\n\n
 * ONLY WORKS WITH POINTERS TO A'S CONTENTS (i.e.  \<type\> = \<typeof(a[0])*\>. typeof is not used because it is not part of the c standard.
 */
#define foreach(item_in_array) SPLIT(foreach_, item_in_array)

/**
 * replacing "in" by ',' allows foreach to use python-like syntax
 */
#define in ,

/**
 * __LINE__ is a predefined macro able to retrieve the line number its called on\n\n
 * X(name) creates a (most likely) unique variable name based on name, used for inner indexes.
 */
#define X(name) (__##name##__LINE__) /* unique variable */

#endif //COMPILERS_FOREACH_H
