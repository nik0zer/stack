#include "tests.h"

int test_one_test()
{

}

int test(char* data_file_name)
{
    FILE* data_file = fopen(data_file_name, "r");
    int num_of_tests = 0;
    fscanf(data_file, "%d", num_of_tests);
    stack* test_stack;
    void* elem_mem;

    for(int test_num = 0; test_num < num_of_tests; test_num++)
    {
        printf("\ntest №%d", test_num);
        
        if(test_one_test() != 0)
        {
            printf("not OK on test %d\n", test_num);
        }
    }

}