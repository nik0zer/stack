#include "stack.h"
#include "tests.h"

int main()
{
    test("test_data");
    ON_CANARY_PROT(printf("CANARY_PROT\n");)
}