#include "stack.h"
#include <stdio.h>
#include <string.h>
#include "tests.h"

int main()
{
    stack a;
    stack* b = &a;
    stack_init(b, sizeof(int));
    printf("%d\n", errno);

    int c = 5, v = 6, j = 7, k = 8, p = 9;
    printf("%d %d %d\n", b->num_of_alloc_stack_elem, b->num_of_elem, errno);
    stack_push(b, &c);
    memcpy(b->stack_pointer, &c, sizeof(c));
    printf("%d %d %d\n", b->num_of_alloc_stack_elem, b->num_of_elem, errno);
    stack_push(b, &c);
    printf("%d %d %d\n", b->num_of_alloc_stack_elem, b->num_of_elem, errno);
    stack_push(b, &c);
    int* g = (int*)malloc(sizeof(int));
    stack_pop(b, g);
    printf("%d %d %d %d\n", *g, b->num_of_alloc_stack_elem, b->num_of_elem, errno);
    memcpy(b->stack_pointer, &c, sizeof(c));
    stack_pop(b, g);
    printf("%d %d %d %d\n", *g, b->num_of_alloc_stack_elem, b->num_of_elem, errno);
    memcpy(b->stack_pointer, &c, sizeof(c));
    stack_pop(b, g);    
    printf("%d %d %d %d\n", *g, b->num_of_alloc_stack_elem, b->num_of_elem, errno);
    
    free(g);
    stack_destroy(b);
}