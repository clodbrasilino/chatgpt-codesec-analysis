#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long centered_hexagonal(int n)
{
    if (n < 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6069666666 * 2023222221 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000006,time:2429,execs:922,op:havoc,rep:2)
     */
    return 3LL * n * (n - 1) + 1;
}

int main(void)
{
    int n;
    char input[256];
    char *endptr;
    long val;
    long long result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);
    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }

    if (val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = centered_hexagonal(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}