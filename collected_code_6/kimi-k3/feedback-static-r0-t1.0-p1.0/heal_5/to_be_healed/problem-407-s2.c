#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int compare_char(const void *a, const void *b)
{
    return (*(const char *)a - *(const char *)b);
}

long next_bigger_number(long n)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char digits[64];
    size_t len;
    size_t i;
    size_t j;
    long result;
    char *endptr;
    
    if (n < 0) {
        return -1;
    }
    
    len = (size_t)snprintf(digits, sizeof(digits), "%ld", n);
    if (len == 0 || len >= sizeof(digits)) {
        return -1;
    }
    
    if (len < 2) {
        return -1;
    }
    
    i = len - 2;
    while (i > 0 && digits[i] >= digits[i + 1]) {
        i--;
    }
    
    if (i == 0 && digits[0] >= digits[1]) {
        return -1;
    }
    
    j = len - 1;
    while (j > i && digits[j] <= digits[i]) {
        j--;
    }
    
    if (j <= i) {
        return -1;
    }
    
    {
        char temp = digits[i];
        digits[i] = digits[j];
        digits[j] = temp;
    }
    
    if (len - i - 1 > 1) {
        qsort(digits + i + 1, len - i - 1, sizeof(char), compare_char);
    }
    
    errno = 0;
    result = strtol(digits, &endptr, 10);
    if (errno == ERANGE || endptr == digits || *endptr != '\0') {
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