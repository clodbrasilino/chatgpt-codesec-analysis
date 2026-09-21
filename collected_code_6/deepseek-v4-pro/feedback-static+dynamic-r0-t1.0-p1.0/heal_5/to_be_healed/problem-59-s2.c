#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long octagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    return (long long)n * (3LL * n - 2LL);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;
    long long result;
    char *endptr;
    long val;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    errno = 0;
    val = strtol(argv[1], &endptr, 10);

    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
        || (errno != 0 && val == 0)) {
        fprintf(stderr, "Error: value out of range\n");
        return 1;
    }

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: not a valid integer\n");
        return 1;
    }

    if (val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Error: value out of integer range\n");
        return 1;
    }

    n = (int)val;

    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return 1;
    }

    result = octagonal_number(n);

    if (result < 0) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}