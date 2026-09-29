#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(uint64_t n)
{
    if (n < UINT64_C(2)) {
        return 0;
    }

    if (n % UINT64_C(2) == 0) {
        return n == UINT64_C(2);
    }

    for (uint64_t divisor = UINT64_C(3);
         divisor <= n / divisor;
         divisor += UINT64_C(2)) {
        if (n % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

static int read_uint64(uint64_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    parsed = strtoumax(buffer, &end, 10);
    if (end == buffer || parsed > UINT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    parsed = strtoumax(buffer, &end, 10);
    if (end == buffer || parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    parsed = strtoimax(buffer, &end, 10);
    if (end == buffer || parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static size_t count_self_inverse_elements(const int64_t *array, size_t length,
                                          uint64_t prime)
{
    size_t count = 0;

    for (size_t i = 0; i < length; ++i) {
        uint64_t residue;

        if (array[i] >= 0) {
            residue = (uint64_t)array[i] % prime;
        } else {
            uint64_t magnitude = (uint64_t)(-(array[i] + 1)) + UINT64_C(1);
            uint64_t remainder = magnitude % prime;
            residue = remainder == 0 ? 0 : prime - remainder;
        }

        if (residue == UINT64_C(1) || residue == prime - UINT64_C(1)) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    uint64_t prime;
    size_t length;
    int64_t *array = NULL;

    if (!read_uint64(&prime) || !read_size(&length)) {
        return EXIT_FAILURE;
    }

    if (!is_prime(prime) || length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_self_inverse_elements(array, length, prime));

    free(array);
    return EXIT_SUCCESS;
}