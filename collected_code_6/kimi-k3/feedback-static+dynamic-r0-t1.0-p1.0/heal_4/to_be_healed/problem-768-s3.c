#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool check_odd_parity(unsigned int num)
{
    bool parity = false;
    
    while (num != 0U)
    {
        parity = !parity;
        num &= (num - 1U);
    }
    
    return parity;
}

int main(void)
{
    unsigned int test_values[] = {0U, 1U, 2U, 3U, 7U, 8U, 15U, 255U};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;
    bool results[8];
    
    for (i = 0U; i < num_tests; i++)
    {
        results[i] = check_odd_parity(test_values[i]);
    }
    
    for (i = 0U; i < num_tests; i++)
    {
        printf("%s\n", results[i] ? "True" : "False");
    }
    
    return 0;
}