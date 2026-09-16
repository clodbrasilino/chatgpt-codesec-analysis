#include <stdio.h>
#include <stdlib.h>

#define MAX_FIB_INDEX 92

static long long fibonacci(int n)
{
    if (n <= 0) {
        return 0LL;
    }
    if (n == 1) {
        return 1LL;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void)
{
    int n = 0;
    int result = 0;

    printf("Enter the index of the Fibonacci number (0-%d): ", MAX_FIB_INDEX);

    result = scanf("%d", &n);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || n > MAX_FIB_INDEX) {
        fprintf(stderr, "Error: index must be between 0 and %d.\n", MAX_FIB_INDEX);
        return EXIT_FAILURE;
    }

    printf("Fibonacci(%d) = %lld\n", n, fibonacci(n));

    return EXIT_SUCCESS;
}