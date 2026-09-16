#include <stdio.h>
#include <stdlib.h>

int tuple_modulo(const int *dividends, const int *divisors, int *results, size_t length)
{
    if (dividends == NULL || divisors == NULL || results == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (divisors[i] == 0) {
            return -2;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        results[i] = dividends[i] % divisors[i];
    }

    return 0;
}

int main(void)
{
    const int first_tuple[] = {10, 20, 30, 40};
    const int second_tuple[] = {3, 6, 7, 9};
    const size_t length = sizeof(first_tuple) / sizeof(first_tuple[0]);
    int *results = malloc(length * sizeof(*results));

    if (results == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != sizeof(second_tuple) / sizeof(second_tuple[0])) {
        fputs("Tuple lengths do not match.\n", stderr);
        free(results);
        return EXIT_FAILURE;
    }

    int status = tuple_modulo(first_tuple, second_tuple, results, length);

    if (status != 0) {
        fputs("Modulo operation failed.\n", stderr);
        free(results);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (size_t i = 0; i < length; ++i) {
        printf("%d%s", results[i], i + 1 < length ? ", " : "");
    }
    puts(")");

    free(results);
    return EXIT_SUCCESS;
}