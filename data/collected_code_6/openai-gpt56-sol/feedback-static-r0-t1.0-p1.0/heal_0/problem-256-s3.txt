#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static size_t count_primes(size_t limit)
{
    if (limit <= 2) {
        return 0;
    }

    if (limit > SIZE_MAX / sizeof(bool)) {
        return 0;
    }

    bool *is_prime = malloc(limit * sizeof(*is_prime));
    if (is_prime == NULL) {
        return 0;
    }

    for (size_t i = 0; i < limit; ++i) {
        is_prime[i] = true;
    }

    is_prime[0] = false;
    is_prime[1] = false;

    for (size_t i = 2; i <= (limit - 1) / i; ++i) {
        if (is_prime[i]) {
            for (size_t j = i * i; j < limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    size_t count = 0;
    for (size_t i = 2; i < limit; ++i) {
        if (is_prime[i]) {
            ++count;
        }
    }

    free(is_prime);
    return count;
}

int main(void)
{
    size_t limit = 0;

    if (scanf("%zu", &limit) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_primes(limit));
    return EXIT_SUCCESS;
}