#include "stack.h"
#include <string.h>
#define NDEBUG
#include <assert.h>

#define START_STACK_SIZE 2
#define STACK_MULTIPLY_CONST 2
#define STACK_DIVIDE_CONST 2
#define STACK_DIVIDE_TRIGGER 4

int canary_struct_value = 0;
int canary_stack_mem_value = 0;

int stack_init(stack* my_stack, int size_of_elem)
{
    errno = NO_ERRORS;

    my_stack->num_of_elem = 0;
    my_stack->offset = 0;
    my_stack->size_of_elem = size_of_elem;
    my_stack->num_of_alloc_stack_elem = 0;
    my_stack->end_canary_of_struct = 0;
    my_stack->start_canary_of_struct = 0;

    my_stack->size_of_stack_mem = 2 * sizeof(canary_stack_mem_value) + START_STACK_SIZE * size_of_elem;

    my_stack->offset = sizeof(canary_stack_mem_value);

    my_stack->stack_pointer = malloc(my_stack->size_of_stack_mem);

    assert(my_stack != NULL);
    if(my_stack == NULL)
    {
        my_stack->size_of_stack_mem = 0;
        errno = CANT_ALLOCATE_MEMORY;
        return CANT_ALLOCATE_MEMORY;
    }

    memcpy(my_stack->stack_pointer, &canary_stack_mem_value, sizeof(canary_stack_mem_value));
    memcpy(my_stack->stack_pointer + my_stack->size_of_stack_mem - sizeof(canary_stack_mem_value), &canary_stack_mem_value,
    sizeof(canary_stack_mem_value));

    my_stack->num_of_alloc_stack_elem = START_STACK_SIZE;

    return NO_ERRORS;
}

int check_stack_valid(stack* my_stack)
{
    assert(my_stack != NULL);
    if(my_stack == NULL)
    {
        errno = NULL_STACK_POINTER;
        return ERROR_IN_CHECK_FUNC;
    }

    if(my_stack->end_canary_of_struct != canary_struct_value || my_stack->start_canary_of_struct != canary_struct_value)
    {
        return STRUCT_CANARIES_INVALID;
    }

    return STACK_VALID;
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

    my_stack->offset = sizeof(canary_stack_mem_value) + my_stack->num_of_elem * my_stack->size_of_elem;

    if(my_stack->num_of_elem >= my_stack->num_of_alloc_stack_elem)
    {
        my_stack->num_of_alloc_stack_elem *= STACK_MULTIPLY_CONST;
        my_stack->size_of_stack_mem = 2 * sizeof(canary_stack_mem_value) + my_stack->num_of_alloc_stack_elem * my_stack->size_of_elem;
        my_stack->stack_pointer = realloc(my_stack->stack_pointer, my_stack->size_of_stack_mem);

        assert(my_stack->stack_pointer != NULL);
        if(my_stack->stack_pointer == NULL)
        {
            errno = CANT_ALLOCATE_MEMORY;
            return CANT_REALLOCATE_MEMORY;
        }

        memcpy(my_stack->stack_pointer, &canary_stack_mem_value, sizeof(canary_stack_mem_value));
        memcpy(my_stack->stack_pointer + my_stack->size_of_stack_mem - sizeof(canary_stack_mem_value), &canary_stack_mem_value,
        sizeof(canary_stack_mem_value));
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

    my_stack->offset = sizeof(canary_stack_mem_value)+ my_stack->num_of_elem * my_stack->size_of_elem;

    memcpy(return_elem, my_stack->stack_pointer + my_stack->offset, my_stack->size_of_elem);

    if(my_stack->num_of_elem <= my_stack->num_of_alloc_stack_elem / STACK_DIVIDE_TRIGGER 
    && my_stack->num_of_alloc_stack_elem / STACK_DIVIDE_TRIGGER != 0)
    {
        my_stack->num_of_alloc_stack_elem /= STACK_DIVIDE_CONST;
        my_stack->size_of_stack_mem = 2 * sizeof(canary_stack_mem_value) + my_stack->num_of_alloc_stack_elem * my_stack->size_of_elem;
        my_stack->stack_pointer = realloc(my_stack->stack_pointer, my_stack->size_of_stack_mem);
        
        assert(my_stack->stack_pointer != NULL);
        if(my_stack->stack_pointer == NULL)
        {
            errno = CANT_ALLOCATE_MEMORY;
            return CANT_REALLOCATE_MEMORY;
        }

        memcpy(my_stack->stack_pointer, &canary_stack_mem_value, sizeof(canary_stack_mem_value));
        memcpy(my_stack->stack_pointer + my_stack->size_of_stack_mem - sizeof(canary_stack_mem_value), &canary_stack_mem_value,
        sizeof(canary_stack_mem_value));
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
