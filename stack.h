#ifndef STACK_H
#define STACK_H

#include <errno.h>

enum stack_errors
{
    NO_ERRORS = 0,
    NULL_POINTER_OF_ELEMENT = 1,
    NULL_buf_ptr = 2,
    NULL_size_IN_STACK = 3,
    CANT_ALLOCATE_MEMORY = 4,
    CANT_REALLOCATE_MEMORY = 5,
    INCORRECT_STACK_VALIDATION = 6,
    ERROR_IN_TEST_FILE_NAME = 7
};

enum stack_valid_check_message
{
    ERROR_IN_CHECK_FUNC = -1,
    STACK_VALID = 0,
    STRUCT_CANARIES_INVALID = 1,
    STACK_MEM_CANARIES_INVALID = 2
};

typedef struct stack
{
    int struct_canary_1;
    void* buf_ptr;
    int size;
    int capasity;
    int size_of_elem;
    int offset;
    int size_of_buf;
    int struct_canary_2;
};

int stack_init(stack* my_stack, int size_of_elem);

int check_stack_valid(stack* my_stack);

int stack_push(stack* my_stack, void* elem);

int stack_pop(stack* my_stack, void* return_elem);

int stack_destroy(stack* my_stack);

void print_stack_error(int error_code);

void print_stack_valid_check_message(int message_code);

#endif