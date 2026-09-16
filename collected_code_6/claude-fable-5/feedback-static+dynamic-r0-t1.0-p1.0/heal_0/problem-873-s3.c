#include <stdio.h>
#include <stdlib.h>

#define MAX_FIB_INDEX 93

static unsigned long long fibonacci(unsigned int n)
{
    if (n < 2U) {
        return (unsigned long long)n;
    }
    return fibonacci(n - 1U) + fibonacci(n - 2U);
}

int main(void)
{
    unsigned int n = 0U;
    int result = 0;

    printf("Enter a non-negative integer (0-%d): ", MAX_FIB_INDEX);

    result = scanf("%u", &n);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n > MAX_FIB_INDEX) {
        fprintf(stderr, "Error: input exceeds maximum supported index of %d.\n", MAX_FIB_INDEX);
        return EXIT_FAILURE;
    }

    printf("fibonacci(%u) = %llu\n", n, fibonacci(n));

    return EXIT_SUCCESS;
}