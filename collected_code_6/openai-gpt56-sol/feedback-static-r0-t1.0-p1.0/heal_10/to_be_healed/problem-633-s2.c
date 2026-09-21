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

static int discard_token_remainder(int character)
{
    while (character != EOF && !is_space_character(character)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    }

    return character == EOF && ferror(stdin) ? -1 : 0;
}

static int read_token(char **token)
{
    enum {
        MAX_TOKEN_LENGTH = 1024
    };

    char *buffer;
    size_t length = 0;
    int character;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character == EOF) {
            return -1;
        }
    } while (is_space_character(character));

    buffer = malloc((size_t)MAX_TOKEN_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    while (character != EOF && !is_space_character(character)) {
        if (length == MAX_TOKEN_LENGTH) {
            free(buffer);
            discard_token_remainder(character);
            return -1;
        }

        buffer[length++] = (char)(unsigned char)character;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int parse_uintmax(uintmax_t maximum, uintmax_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > maximum) {
        free(token);
        return -1;
    }

    free(token);
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