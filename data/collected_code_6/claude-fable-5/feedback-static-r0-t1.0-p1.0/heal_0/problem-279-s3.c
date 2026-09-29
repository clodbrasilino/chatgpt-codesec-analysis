#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int is_decagonal_input_valid(long n)
{
    if (n < 1L) {
        return 0;
    }
    if (n > 23170L) {
        return 0;
    }
    return 1;
}

static long nth_decagonal(long n)
{
    return (4L * n * n) - (3L * n);
}

int main(void)
{
    long n = 0L;
    long result = 0L;
    int scan_status = 0;

    printf("Enter the value of n: ");
    scan_status = scanf("%ld", &n);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_decagonal_input_valid(n) == 0) {
        fprintf(stderr, "Error: n must be between 1 and 23170.\n");
        return EXIT_FAILURE;
    }

    result = nth_decagonal(n);
    printf("The %ld-th decagonal number is: %ld\n", n, result);

    return EXIT_SUCCESS;
}