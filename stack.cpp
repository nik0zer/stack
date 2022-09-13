#include "stack.h"
#include <string.h>
#define NDEBUG
#include <assert.h>

#define START_STACK_SIZE 2
#define STACK_MULTIPLY_CONST 2
#define STACK_DIVIDE_CONST 2
#define STACK_DIVIDE_TRIGGER 4

int canary_value = 0;

int stack_init(stack* new_stack, int size_of_elem)
{
    errno = NO_ERRORS;

    new_stack->num_of_elem = 0;
    new_stack->offset = 0;
    new_stack->size_of_elem = size_of_elem;
    new_stack->num_of_alloc_stack_elem = 0;
    new_stack->end_canary_of_struct = 0;
    new_stack->start_canary_of_struct = 0;

    new_stack->stack_pointer = calloc(START_STACK_SIZE, size_of_elem);
    
    assert(new_stack != NULL);
    if(new_stack == NULL)
    {
        errno = CANT_ALLOCATE_MEMORY;
        return CANT_ALLOCATE_MEMORY;
    }

    new_stack->num_of_alloc_stack_elem = START_STACK_SIZE;

    return NO_ERRORS;
}

int check_stack_valid(stack* my_stack)
{
    assert(my_stack != NULL);
    if(my_stack == NULL)
    {
        errno = NULL_STACK_POINTER;
        return ERROR_IN_CHECK_FUNС;
    }

    if(my_stack->end_canary_of_struct != canary_value || my_stack->start_canary_of_struct != canary_value)
    {
        return STRUCT_CANARIES_INVALID;
    }
}

int stack_push(stack* my_stack, void* elem)
{
    errno = NO_ERRORS;

    assert(elem != NULL);
    if(elem == NULL)
    {
        errno = NULL_POINTER_OF_ELEMENT;
        return NULL_POINTER_OF_ELEMENT;
    }

    assert(my_stack != NULL);
    if(my_stack == NULL)
    {
        errno = NULL_STACK_POINTER;
        return NULL_STACK_POINTER;
    }

    my_stack->offset = my_stack->num_of_elem * my_stack->size_of_elem;

    if(my_stack->num_of_elem >= my_stack->num_of_alloc_stack_elem)
    {
        my_stack->num_of_alloc_stack_elem *= STACK_MULTIPLY_CONST;
        my_stack->stack_pointer = realloc(my_stack->stack_pointer, my_stack->num_of_alloc_stack_elem * my_stack->size_of_elem);

        assert(my_stack->stack_pointer != NULL);
        if(my_stack->stack_pointer == NULL)
        {
            errno = CANT_ALLOCATE_MEMORY;
            return CANT_REALLOCATE_MEMORY;
        }
    }

    memcpy(my_stack->stack_pointer + my_stack->offset, elem, my_stack->size_of_elem);
    my_stack->num_of_elem++;

    return NO_ERRORS;
}

int stack_pop(stack* my_stack, void* return_elem)
{
    errno = NO_ERRORS;

    assert(my_stack != NULL);
    if(my_stack == NULL)
    {
        return NULL_STACK_POINTER;
    }

    assert(return_elem != NULL);
    if(return_elem == NULL)
    {
        return NULL_POINTER_OF_ELEMENT;
    }

    assert(my_stack->num_of_elem != NULL);
    if(my_stack->num_of_elem == 0)
    {
        errno = NULL_NUM_OF_ELEM_IN_STACK;
        return NULL_NUM_OF_ELEM_IN_STACK;
    }

    my_stack->num_of_elem--;

    my_stack->offset = my_stack->num_of_elem * my_stack->size_of_elem;

    memcpy(return_elem, my_stack->stack_pointer + my_stack->offset, my_stack->size_of_elem);

    if(my_stack->num_of_elem <= my_stack->num_of_alloc_stack_elem / STACK_DIVIDE_TRIGGER 
    && my_stack->num_of_alloc_stack_elem / STACK_DIVIDE_TRIGGER != 0)
    {
        my_stack->num_of_alloc_stack_elem /= STACK_DIVIDE_CONST;
        my_stack->stack_pointer = realloc(my_stack->stack_pointer, my_stack->num_of_alloc_stack_elem * my_stack->size_of_elem);

        assert(my_stack->stack_pointer != NULL);
        if(my_stack->stack_pointer == NULL)
        {
            errno = CANT_ALLOCATE_MEMORY;
            return CANT_REALLOCATE_MEMORY;
        }
    }

    return NO_ERRORS;
}

int stack_destroy(stack* my_stack)
{
    errno = NO_ERRORS;

    assert(my_stack != NULL);
    if(my_stack == NULL)
    {
        errno = NULL_STACK_POINTER;
        return NULL_STACK_POINTER;
    }

    free(my_stack->stack_pointer);

    return NO_ERRORS;
}
