#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

static size_t count_primes(size_t limit)
{
    if (limit <= 2U) {
        return 0U;
    }

    bool *is_prime = malloc(limit * sizeof(*is_prime));
    if (is_prime == NULL) {
        return SIZE_MAX;
    }

    for (size_t i = 0U; i < limit; ++i) {
        is_prime[i] = true;
    }

    is_prime[0] = false;
    is_prime[1] = false;

    for (size_t i = 2U; i <= (limit - 1U) / i; ++i) {
        if (is_prime[i]) {
            for (size_t multiple = i * i; multiple < limit; multiple += i) {
                is_prime[multiple] = false;
            }
        }
    }

    size_t count = 0U;
    for (size_t i = 2U; i < limit; ++i) {
        if (is_prime[i]) {
            ++count;
        }
    }

    free(is_prime);
    return count;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long value = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid non-negative integer\n");
        return EXIT_FAILURE;
    }

    if (value > SIZE_MAX || (size_t)value > SIZE_MAX / sizeof(bool)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    size_t count = count_primes((size_t)value);
    if (count == SIZE_MAX) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}