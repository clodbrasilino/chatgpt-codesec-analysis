#include <stdio.h>
#include <stdlib.h>

static int tuple_modulo(const int *dividends, const int *divisors,
                        int *results, size_t length)
{
    if (dividends == NULL || divisors == NULL || results == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (divisors[i] == 0) {
            return -1;
        }
        results[i] = dividends[i] % divisors[i];
    }

    return 0;
}

int main(void)
{
    const int tuple1[] = {10, 20, 30, 40};
    const int tuple2[] = {3, 6, 7, 9};
    const size_t length = sizeof(tuple1) / sizeof(tuple1[0]);
    int *results = calloc(length, sizeof(*results));

    if (results == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (tuple_modulo(tuple1, tuple2, results, length) != 0) {
        fputs("Modulo operation failed\n", stderr);
        free(results);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (size_t i = 0; i < length; ++i) {
        printf("%d%s", results[i], i + 1U < length ? ", " : "");
    }
    puts(")");

    free(results);
    return EXIT_SUCCESS;
}