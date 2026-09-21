#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_pairwise_xor(const uint64_t *array, size_t length,
                            uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL || (length != 0 && array == NULL)) {
        return 0;
    }

#if SIZE_MAX > UINT64_MAX
    if (length > UINT64_MAX) {
        return 0;
    }
#endif

    for (unsigned int bit = 0; bit < 64U; ++bit) {
        uint64_t ones = 0;
        uint64_t zeros;
        uint64_t differing_pairs;
        uint64_t contribution;

        for (size_t i = 0; i < length; ++i) {
            ones += (array[i] >> bit) & UINT64_C(1);
        }

        zeros = (uint64_t)length - ones;

        if (ones != 0 && zeros > UINT64_MAX / ones) {
            return 0;
        }

        differing_pairs = ones * zeros;

        if (differing_pairs > (UINT64_MAX >> bit)) {
            return 0;
        }

        contribution = differing_pairs << bit;

        if (sum > UINT64_MAX - contribution) {
            return 0;
        }

        sum += contribution;
    }

    *result = sum;
    return 1;
}

static int is_space(int c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static int read_uintmax_token(uintmax_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end;
    uintmax_t parsed;
    size_t length;

    if (value == NULL) {
        return 0;
    }

    do {
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            return 0;
        }

        length = 0;
        while (buffer[length] != '\0' && is_space((unsigned char)buffer[length])) {
            ++length;
        }
    } while (buffer[length] == '\0');

    if (length != 0) {
        size_t source = length;
        size_t destination = 0;

        while (buffer[source] != '\0') {
            buffer[destination++] = buffer[source++];
        }
        buffer[destination] = '\0';
    }

    length = 0;
    while (buffer[length] != '\0' && !is_space((unsigned char)buffer[length])) {
        ++length;
    }

    if (buffer[length] == '\0' && length == sizeof buffer - 1 &&
        buffer[length - 1] != '\n') {
        int c;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            c = fgetc(stdin);
        } while (c != EOF && !is_space(c));

        return 0;
    }

    buffer[length] = '\0';

    if (length == 0 || buffer[0] == '+' || buffer[0] == '-') {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            return 0;
        }
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !read_uintmax_token(&parsed) || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !read_uintmax_token(&parsed) ||
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

#if SIZE_MAX > UINT64_MAX
    if (length > UINT64_MAX) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }
#endif

    if (length > SIZE_MAX / sizeof *array) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof *array);
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

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}