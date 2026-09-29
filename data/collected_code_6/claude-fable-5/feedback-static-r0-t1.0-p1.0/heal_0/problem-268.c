#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long star_number(unsigned int n, int *error)
{
    long long result;
    long long ln;

    if (error == NULL) {
        return -1;
    }

    *error = 0;

    if (n == 0U) {
        *error = 1;
        return -1;
    }

    ln = (long long)n;

    if (ln > 1000000000LL) {
        *error = 1;
        return -1;
    }

    result = 6LL * ln * (ln - 1LL) + 1LL;

    return result;
}

int main(void)
{
    unsigned int n;
    int error;
    long long result;
    int scan_status;

    printf("Enter n: ");

    scan_status = scanf("%u", &n);
    if (scan_status != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = star_number(n, &error);
    if (error != 0) {
        fprintf(stderr, "Value out of supported range\n");
        return EXIT_FAILURE;
    }

    printf("The %u'th star number is: %lld\n", n, result);

    return EXIT_SUCCESS;
}