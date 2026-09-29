#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_pairwise_xor(const uint64_t *array, size_t length,
                            uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL || (array == NULL && length != 0)) {
        return -1;
    }

#if SIZE_MAX > UINT64_MAX
    if (length > UINT64_MAX) {
        return -1;
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
            return -1;
        }

        differing_pairs = ones * zeros;

        if (differing_pairs > (UINT64_MAX >> bit)) {
            return -1;
        }

        contribution = differing_pairs << bit;

        if (sum > UINT64_MAX - contribution) {
            return -1;
        }

        sum += contribution;
    }

    *result = sum;
    return 0;
}

static int is_space_character(int character)
{
    return character == ' ' || character == '\t' ||
           character == '\r' || character == '\n' ||
           character == '\v' || character == '\f';
}

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int character;

    if (buffer == NULL || capacity < 2U) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character == EOF) {
            return -1;
        }
    } while (is_space_character(character));

    while (character != EOF && !is_space_character(character)) {
        if (length + 1U >= capacity) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != EOF && !is_space_character(character));

            return -1;
        }

        buffer[length++] = (char)(unsigned char)character;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    }

    if (character == EOF && ferror(stdin)) {
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

static int parse_uintmax(uintmax_t maximum, uintmax_t *value)
{
    enum {
        TOKEN_CAPACITY = 1025
    };

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[TOKEN_CAPACITY];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(token, sizeof(token)) != 0) {
        return -1;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > maximum) {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        parse_uintmax((uintmax_t)SIZE_MAX, &parsed) != 0) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        parse_uintmax((uintmax_t)UINT64_MAX, &parsed) != 0) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    size_t length;
    uint64_t *array = NULL;
    uint64_t result;

    if (read_size(&length) != 0) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

#if SIZE_MAX > UINT64_MAX
    if (length > UINT64_MAX) {
        return EXIT_FAILURE;
    }
#endif

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_uint64(&array[i]) != 0) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (sum_pairwise_xor(array, length, &result) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}