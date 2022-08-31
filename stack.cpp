#include "stack.h"
#include <string.h>

int stack_init(stack* new_stack, int size_of_elem)
{
    new_stack->num_of_elem = 0;
    new_stack->size_of_elem = size_of_elem;
    new_stack->size_of_stack = START_STACK_SIZE;
    new_stack->stack_pointer = calloc(START_STACK_SIZE, size_of_elem);
    return NO_ERRORS;
}

int stack_push(stack* my_stack, void* elem)
{
    if(elem == NULL)
    {
        return NULL_POINTER_OF_ELEMENT;
    }
    if(my_stack == NULL)
    {
        return NULL_STACK_POINTER;
    }
    int offset = my_stack->num_of_elem * my_stack->size_of_elem;
    if(my_stack->num_of_elem < my_stack->size_of_stack)
    {
        memcpy(my_stack->stack_pointer + offset, elem, my_stack->size_of_elem);
        my_stack->num_of_elem++;
    }
    else
    {
        my_stack->size_of_stack *= STACK_MULTIPLY_CONST;
        my_stack->stack_pointer = realloc(my_stack->stack_pointer, my_stack->size_of_stack * my_stack->size_of_elem);
        memcpy(my_stack->stack_pointer + offset, elem, my_stack->size_of_elem);
        my_stack->num_of_elem++;
    }
    return NO_ERRORS;
}

int stack_pop(stack* my_stack, void* return_elem)
{
    if(my_stack == NULL)
    {
        return NULL_STACK_POINTER;
    }
    if(return_elem == NULL)
    {
        return NULL_POINTER_OF_ELEMENT;
    }
    if(my_stack->num_of_elem == 0)
    {
        return NULL_NUM_OF_ELEM_IN_STACK;
    }
    my_stack->num_of_elem--;
    int offset = my_stack->num_of_elem * my_stack->size_of_elem;
    memcpy(return_elem, my_stack->stack_pointer + offset, my_stack->size_of_elem);
    if(my_stack->num_of_elem <= my_stack->size_of_stack / STACK_DIVIDE_TRIGGER && my_stack->size_of_stack / STACK_DIVIDE_TRIGGER != 0)
    {
        my_stack->size_of_stack /= STACK_DIVIDE_CONST;
        my_stack->stack_pointer = realloc(my_stack->stack_pointer, my_stack->size_of_stack * my_stack->size_of_elem);
    }
    return NO_ERRORS;
}

int stack_destroy(stack* my_stack)
{
    if(my_stack == NULL)
    {
        return NULL_STACK_POINTER;
    }
    free(my_stack->stack_pointer);
    return NO_ERRORS;
}
