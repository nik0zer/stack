#include "tests.h"

int test_one_test(FILE* data_file, stack* test_stack_ptr)
{
    stack_init(test_stack_ptr, sizeof(int));
    int command_num = 0;
    int test_valid = 1;
    while(true)
    {
        int command_code = 0;
        fscanf(data_file, "%d", &command_code);
        switch (command_code)
        {
        case 0:
        {
            int push_int = 0;
            fscanf(data_file, "%d", &push_int);
            stack_push(test_stack_ptr, &push_int);
            break;
        }
        case 1:
        {
            int correct_pop_int = 0;
            int correct_error_code = 0;
            int pop_int = 0;
            int error_code = 0; 
            fscanf(data_file, "%d %d", &correct_pop_int, &correct_error_code);
            error_code = stack_pop(test_stack_ptr, &pop_int);
            if(pop_int != correct_pop_int)
            {
                printf("ERROR IN COMAND №%d POP RETURN INCORRECT INT(returned int: %d)\n", command_num, pop_int);
                test_valid = 0;
            }
            if(error_code != correct_error_code)
            {
                printf("ERROR IN COMAND №%d POP RETURN INCORRECT ERROR CODE(returned error code: %d)\n", command_num, error_code);
                test_valid = 0;
            }
            break;
        }
        case -1:
        {
            stack_destroy(test_stack_ptr);
            return test_valid;
            break;
        }
        }
        command_num++;
    }
}


int test(char* data_file_name)
{
    FILE* data_file = fopen(data_file_name, "r");
    if(data_file == NULL)
    {
        return ERROR_IN_TEST_FILE_NAME;
    }
    stack* test_stack_ptr = (stack*)malloc(sizeof(stack));
    int num_of_tests = 0;
    fscanf(data_file, "%d", &num_of_tests);
    for(int num_of_curr_test = 0; num_of_curr_test < num_of_tests; num_of_curr_test++)
    {
        printf("TEST №%d\n", num_of_curr_test);
        if(test_one_test(data_file, test_stack_ptr))
        {
            printf("TEST №%d OK\n", num_of_curr_test);
        }
        else
        {
            printf("TEST №%d NOT OK\n", num_of_curr_test);
        }
    }
    free(test_stack_ptr);
    return NO_ERRORS;
}

