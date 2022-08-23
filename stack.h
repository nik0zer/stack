#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#define START_STACK_SIZE 2
#define STACK_MULTIPLY_CONST

enum stack_errors
{
    NO_ERRORS = 0,
    NULL_POINTER_OF_ELEMENT = 1,
    NULL_STACK_POINTER = 2
};

typedef struct
{
    void* stack_pointer;
    int num_of_elem;
    int size_of_stack;
    int size_of_elem;
} stack;

int stack_push(stack* my_stack, void* elem);

#endif