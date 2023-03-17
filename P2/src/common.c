//
// Created by Rafael Bardisa Rodes on 13/2/23.
//

#include "common.h"


size_t file_size(FILE* infile){

    fseek(infile, 0L, SEEK_END);

    //narrowing conversion, is only a problem for very large files
    size_t size = ftell(infile);
    rewind(infile);

    return size;
}

char* join_(char* buffer, int argc, ...){
    buffer[0] = '\0';

    va_list argv;
    int i;

    // initialize argv to get data from the variable arguments
    va_start(argv, argc);

    /* access all the arguments assigned to valist */
    for (i = 0; i < argc; i++) {
    // retrieve ansi code and concatenate into buffer
    strcat(buffer, va_arg(argv, char*));
    }
    /* clean memory reserved for valist */
    va_end(argv);

    return buffer;
}

size_t joint_len(int argc, ...){
    size_t length = 1;

    va_list argv;

    // initialize argv to get data from the variable arguments
    va_start(argv, argc);

    /* access all the arguments assigned to valist */
    for (int i = 0; i < argc; i++) {
        // retrieve ansi code and concatenate into buffer
        length += strlen(va_arg(argv, char*));
    }
    /* clean memory reserved for valist */
    va_end(argv);

    return length;
}

Stack Stack_create(size_t capacity, size_t element_size){
    Stack result = {
            .contents = calloc(capacity, element_size),
            .capacity = capacity,
            .element_size = element_size,
            .size = 0,
    };
    return result;
}

void Stack_delete(Stack* stack){
    free(stack->contents);
}

Option_void pop(Stack* stack){
    //null result is invalid
    Option_void result = {0};
    if(!stack->size) return result;

    //pop is successful
    stack->size--;
    int top = stack->size * stack->element_size;

    result.ok = 1;
    result.value = &stack->contents[top];

    //debug, assumes int contents
    //printf("%s%i%s", FMT(BLUE), *(int*)&stack->contents[top], FMT(CLEAR));

    return result;
}

int push(Stack* stack, void* element){
    //if stack is full, do nothing
    if (stack->size == stack->capacity) return 1;

    //copies memory into void array, forcing polymorphism through memory management
    int top = stack->size * stack->element_size;
    memcpy(&stack->contents[top], element, stack->element_size);

    //debug, assumes int contents
    //printf("%s%i%s", FMT(RED), *(int*)&stack->contents[top], FMT(CLEAR));
    stack->size++;

    return 0;
}
