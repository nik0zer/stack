#include "stack.h"
#include "tests.h"

int main()
{
    ON_CANARY_PROT(printf("CANARY_PROT\n");)
    test("test_data");
}