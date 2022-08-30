#include "stack.h"
#include <stdio.h>

int main()
{
    stack a;
    stack* b = &a;
    stack_init(b, sizeof(int));

    int c = 5, v = 6, j = 7, k = 8, p = 9;
    stack_push(b, &c);
    int* g = (int*)malloc(sizeof(int));
    stack_pop(b, g);
    stack_pop(b, g);
    printf("%d %d", *g, b->size_of_stack);
    
    free(g);
    stack_destroy(b);
}