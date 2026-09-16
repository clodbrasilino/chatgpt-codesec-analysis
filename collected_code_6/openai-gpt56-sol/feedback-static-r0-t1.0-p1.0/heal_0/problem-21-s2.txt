#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int print_multiples(long long n, size_t m)
{
    for (size_t i = 1; i <= m; ++i) {
        if (n > 0 && i > (size_t)(LLONG_MAX / n)) {
            return -1;
        }

        if (n < 0 && i > (size_t)(LLONG_MIN / n)) {
            return -1;
        }

        printf("%lld\n", n * (long long)i);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    long long n;
    unsigned long long count;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoll(argv[1], &end, 10);
    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    count = strtoull(argv[2], &end, 10);
    if (errno == ERANGE || end == argv[2] || *end != '\0' ||
        argv[2][0] == '-' || count > SIZE_MAX || count > LLONG_MAX) {
        fprintf(stderr, "Invalid value for m\n");
        return EXIT_FAILURE;
    }

    if (print_multiples(n, (size_t)count) != 0) {
        fprintf(stderr, "Integer overflow while calculating multiples\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}