#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int is_lucid(unsigned long long value)
{
    if (value == 0) {
        return 0;
    }

    while (value != 0) {
        unsigned int digit = (unsigned int)(value % 10ULL);

        if (digit != 5U && digit != 6U) {
            return 0;
        }

        value /= 10ULL;
    }

    return 1;
}

static int get_lucid_number(unsigned long long n, unsigned long long *result)
{
    if (result == NULL || n < 5ULL) {
        return 0;
    }

    for (;;) {
        if (is_lucid(n)) {
            *result = n;
            return 1;
        }

        if (n == 5ULL) {
            break;
        }

        --n;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long n;
    unsigned long long result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!get_lucid_number(n, &result)) {
        fprintf(stderr, "No lucid number is less than or equal to %llu\n", n);
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);
    return EXIT_SUCCESS;
}