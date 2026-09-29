#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static long long perrin(int n);

static long long perrin(int n)
{
    long long a = 3LL;
    long long b = 0LL;
    long long c = 2LL;
    /* Possible weaknesses found:
     *  Variable 'next' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'next' can be reduced. [variableScope]
     */
    long long next = 0LL;
    int i = 0;

    if (n == 0) {
        return a;
    }
    if (n == 1) {
        return b;
    }
    if (n == 2) {
        return c;
    }

    for (i = 3; i <= n; i++) {
        next = a + b;
        a = b;
        b = c;
        c = next;
    }

    return c;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *endptr = NULL;
    long value = 0L;
    long long result = 0LL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: invalid number '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (value < 0L || value > 90L) {
        fprintf(stderr, "Error: n must be between 0 and 90\n");
        return EXIT_FAILURE;
    }

    result = perrin((int)value);

    if (printf("Perrin(%ld) = %lld\n", value, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}