#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_divisors(int n)
{
    int count = 0;
    int i;
    unsigned int abs_n;
    
    if (n == 0) {
        return 0;
    }
    
    abs_n = (n < 0) ? (unsigned int)(-(n + 1)) + 1U : (unsigned int)n;
    
    for (i = 1; i <= (int)(abs_n / (unsigned int)i); i++) {
        unsigned int ui = (unsigned int)i;
        if (abs_n % ui == 0U) {
            unsigned int other = abs_n / ui;
            count = (ui == other) ? (count + 1) : (count + 2);
        }
    }
    
    return count;
}

int main(void)
{
    int test_values[] = {1, 12, 36, 100, 97, -48, 0, INT_MAX, INT_MIN};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;
    
    for (i = 0; i < num_tests; i++) {
        int result = count_divisors(test_values[i]);
        printf("Number of divisors of %d: %d\n", test_values[i], result);
    }
    
    return EXIT_SUCCESS;
}