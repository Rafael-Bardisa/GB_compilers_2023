//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#ifndef COMPILERS_COMMON_H
#define COMPILERS_COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "optional.h"
#include "foreach.h"
#include "format.h"

// defining NO_FMT replaces all calls to FMT() by "", essentially deactivating the macro

#define TRUE 1
#define FALSE 0

#define NARGS(...) (sizeof((char*[]){__VA_ARGS__})/sizeof(char*))
/**
 * ugly way to create and write into a buffer the string concatenations of the next n arguments.
 */
#define join(buffer, ...) char buffer[joint_len(NARGS(__VA_ARGS__), __VA_ARGS__)]; \
join_(buffer, NARGS(__VA_ARGS__), __VA_ARGS__);

#define SIGMA "\U000003A3"
#define getName(var) #var

typedef optional(int) Option_int;
typedef optional_ref(void) Option_void;

/**
 * bool structure if needed
 */
typedef enum bool_{
    false = FALSE,
    true = TRUE,
} bool;

#define USE_ISIN(type) static bool isin_##type(const type *container, size_t container_size, type element) {\
for (int i = 0; i < container_size; i++) {\
if (container[i] == element) { return 1; }\
}\
return 0;\
}

// defines isin_int
USE_ISIN(int)


/**
 * Given a file, return the length of the file in bytes (equivalent to characters if file is encoded in ASCII)<br>
 * Resets the file position indicator back to the start of the file!
 * @param infile pointer to the file to calculate the length of
 * @return the length of the file in characters
 * TODO error checking
 */
size_t file_size(FILE* infile);

/**
 * join a variadic list of strings into buffer argument
 * @param buffer where to store the concatenation of all strigns
 * @param argc number of strings to concatenate
 * @param ... the strings to concatenate
 * @return same buffer pointer
 */
char* join_(char* buffer, int argc, ...);

/**
 * get joint length of all strings in variadic arguments
 * @param argc number of strings
 * @param ... the (null terminated) strings
 * @return joint size of all strings
 */
size_t joint_len(int argc, ...);

//stack
typedef struct stack{
    // heap allocated pointer to store the contents
    void* contents;
    // current stack size
    size_t size;
    // maximum stack capacity
    size_t capacity;
    // size of stored structure (cannot be dynamic)
    size_t element_size;
}Stack;

/**
 * Creates a generic stack for storing whatever. Your responsibility to know what data type you want
 * @param capacity how many elements are allowed in the stack at most
 * @param element_size the size of each element
 * @return a stack
 */
Stack Stack_create(size_t capacity, size_t element_size);

/**
 * frees the memory associated with a stack
 * @param stack the stack to free
 */
void Stack_free(Stack* stack);

/**
 * return the top element from a stack and remove it from the container
 * @param stack the stack to get the top element from
 * @return optional memory address to the element
 */
Option_void pop(Stack* stack);

/**
 * push an arbitrary element into the stack
 * @param stack a stack
 * @param element whatever you want my friend
 * @return a status int. 0 is good
 */
int push(Stack* stack, void* element);

#endif //COMPILERS_COMMON_H
