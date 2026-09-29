#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_pairwise_xor(const uint64_t *array, size_t length, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL || (length != 0 && array == NULL)) {
        return 0;
    }

    for (unsigned int bit = 0; bit < 64U; ++bit) {
        size_t ones = 0;

        for (size_t i = 0; i < length; ++i) {
            ones += (size_t)((array[i] >> bit) & UINT64_C(1));
        }

        size_t zeros = length - ones;

        if (ones != 0 && zeros > UINT64_MAX / ones) {
            return 0;
        }

        uint64_t differing_pairs = (uint64_t)ones * (uint64_t)zeros;

        if (bit == 63U) {
            if (differing_pairs != 0) {
                return 0;
            }
        } else {
            if (differing_pairs > (UINT64_MAX >> bit)) {
                return 0;
            }

            uint64_t contribution = differing_pairs << bit;

            if (sum > UINT64_MAX - contribution) {
                return 0;
            }

            sum += contribution;
        }
    }

    *result = sum;
    return 1;
}

static int read_token(char *buffer, size_t size)
{
    int c;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    do {
        c = getchar();
    } while (c != EOF && (c == ' ' || c == '\t' || c == '\n' ||
                          c == '\r' || c == '\f' || c == '\v'));

    if (c == EOF) {
        return 0;
    }

    do {
        if (length + 1 >= size) {
            do {
                c = getchar();
            } while (c != EOF && c != ' ' && c != '\t' && c != '\n' &&
                     c != '\r' && c != '\f' && c != '\v');
            return 0;
        }

        buffer[length++] = (char)c;
        c = getchar();
    } while (c != EOF && c != ' ' && c != '\t' && c != '\n' &&
             c != '\r' && c != '\f' && c != '\v');

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char buffer[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    size_t length;
    uint64_t *array = NULL;
    uint64_t result;

    if (!read_size(&length)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (!read_uint64(&array[i])) {
                fputs("Invalid input\n", stderr);
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    if (!sum_pairwise_xor(array, length, &result)) {
        fputs("Result overflow\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}