#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

bool has_even_divisor_count(long long n)
{
    if (n <= 0)
    {
        return false;
    }
    
    if (n > LLONG_MAX - 1)
    {
        return false;
    }
    
    long long root = (long long)sqrt((double)n);
    
    while (root * root > n)
    {
        root--;
    }
    while ((root + 1) * (root + 1) <= n && root + 1 <= LLONG_MAX / (root + 1))
    {
        root++;
    }
    
    return (root * root != n);
}

int main(void)
{
    long long test_values[] = {1, 4, 9, 16, 25, 36, 2, 3, 5, 6, 7, 8, 10, 12};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;
    
    for (i = 0; i < num_tests; i++)
    {
        if (test_values[i] > 0)
        {
            bool is_even = has_even_divisor_count(test_values[i]);
            printf("%lld: %s\n", test_values[i], is_even ? "even" : "odd");
        }
    }
    
    return 0;
}