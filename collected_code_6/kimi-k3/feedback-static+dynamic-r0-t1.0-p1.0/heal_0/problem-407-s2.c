#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int compare_char(const void *a, const void *b)
{
    return (*(const char *)a - *(const char *)b);
}

long next_bigger_number(long n)
{
    char digits[32];
    int len;
    int i;
    int j;
    long result;
    
    if (n < 0) {
        return -1;
    }
    
    len = snprintf(digits, sizeof(digits), "%ld", n);
    if (len < 0 || len >= (int)sizeof(digits)) {
        return -1;
    }
    
    i = len - 2;
    while (i >= 0 && digits[i] >= digits[i + 1]) {
        i--;
    }
    
    if (i < 0) {
        return -1;
    }
    
    j = len - 1;
    while (digits[j] <= digits[i]) {
        j--;
    }
    
    {
        char temp = digits[i];
        digits[i] = digits[j];
        digits[j] = temp;
    }
    
    qsort(digits + i + 1, (size_t)(len - i - 1), sizeof(char), compare_char);
    
    result = strtol(digits, NULL, 10);
    if (result == LONG_MAX || result == LONG_MIN) {
        return -1;
    }
    
    return result;
}

int main(void)
{
    long test_cases[] = {12, 513, 2017, 9, 111, 531, 123456789};
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    size_t i;
    
    for (i = 0; i < num_tests; i++) {
        long result = next_bigger_number(test_cases[i]);
        if (result == -1) {
            printf("%ld: no bigger number possible\n", test_cases[i]);
        } else {
            printf("%ld: %ld\n", test_cases[i], result);
        }
    }
    
    return 0;
}