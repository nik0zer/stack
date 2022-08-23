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
    if(my_stack->num_of_elem < my_stack->size_of_stack)
    {
        int offset = my_stack->num_of_elem * my_stack->size_of_elem;
        memcpy(my_stack->stack_pointer + offset, elem, my_stack->size_of_elem);
        my_stack->num_of_elem++;
        return NO_ERRORS;
    }
    else
    {
        
    }
    return NO_ERRORS;
}