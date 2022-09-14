#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

enum stack_errors
{
    NO_ERRORS = 0,
    NULL_POINTER_OF_ELEMENT = 1,
    NULL_STACK_POINTER = 2,
    NULL_NUM_OF_ELEM_IN_STACK = 3,
    CANT_ALLOCATE_MEMORY = 4,
    CANT_REALLOCATE_MEMORY = 5,
    INCORRECT_STACK_VALIDATION = 6
};

enum stack_valid_check_message
{
    ERROR_IN_CHECK_FUNC = -1,
    STACK_VALID = 0,
    STRUCT_CANARIES_INVALID = 1,
    STACK_MEM_CANARIES_INVALID = 2
};

typedef struct
{
    int start_canary_of_struct;
    void* stack_pointer;
    int num_of_elem;
    int num_of_alloc_stack_elem;
    int size_of_elem;
    int offset;
    int size_of_stack_mem;
    int end_canary_of_struct;
} stack;

int stack_init(stack* new_stack, int size_of_elem);

int check_stack_valid(stack* my_stack);

int stack_push(stack* my_stack, void* elem);

int stack_pop(stack* my_stack, void* return_elem);

int stack_destroy(stack* my_stack);

#endif