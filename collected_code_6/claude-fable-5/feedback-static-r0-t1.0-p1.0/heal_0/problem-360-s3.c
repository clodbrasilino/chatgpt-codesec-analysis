#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long carol_number(int n, int *error);

long long carol_number(int n, int *error)
{
    long long p;
    long long result;

    if (error == NULL) {
        return 0;
    }

    if (n < 1 || n > 31) {
        *error = 1;
        return 0;
    }

    p = (1LL << n) - 1LL;
    result = p * p - 2LL;
    *error = 0;
    return result;
}

int main(void)
{
    int n;
    int error;
    long long result;
    int scan_status;

    printf("Enter n (1 to 31): ");
    scan_status = scanf("%d", &n);

    if (scan_status != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    error = 0;
    result = carol_number(n, &error);

    if (error != 0) {
        fprintf(stderr, "n must be between 1 and 31.\n");
        return EXIT_FAILURE;
    }

    printf("Carol number %d is %lld\n", n, result);
    return EXIT_SUCCESS;
}