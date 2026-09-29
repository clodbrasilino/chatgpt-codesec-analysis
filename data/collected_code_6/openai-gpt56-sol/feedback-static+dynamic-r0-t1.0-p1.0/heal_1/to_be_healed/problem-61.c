#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int count_substrings(const char *digits, uint64_t *result)
{
    size_t length;
    size_t table_size;
    uint64_t *frequencies;
    int64_t prefix = 0;
    int64_t offset;
    uint64_t count = 0;

    if (digits == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(digits);
    if (length > (SIZE_MAX - 1U) / 9U) {
        return -1;
    }

    table_size = 9U * length + 1U;
    if (table_size > SIZE_MAX / sizeof(*frequencies)) {
        return -1;
    }

    frequencies = calloc(table_size, sizeof(*frequencies));
    if (frequencies == NULL) {
        return -1;
    }

    offset = (int64_t)length;
    frequencies[(size_t)offset] = 1U;

    for (size_t i = 0; i < length; ++i) {
        unsigned int digit;

        if (!isdigit((unsigned char)digits[i])) {
            free(frequencies);
            return -1;
        }

        digit = (unsigned int)(digits[i] - '0');
        prefix += (int64_t)digit - 1;

        if (frequencies[(size_t)(prefix + offset)] > UINT64_MAX - count) {
            free(frequencies);
            return -1;
        }

        count += frequencies[(size_t)(prefix + offset)];

        if (frequencies[(size_t)(prefix + offset)] == UINT64_MAX) {
            free(frequencies);
            return -1;
        }

        ++frequencies[(size_t)(prefix + offset)];
    }

    free(frequencies);
    *result = count;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t input_length;
    uint64_t count;

    errno = 0;
    input_length = getline(&input, &capacity, stdin);
    if (input_length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    while (input_length > 0 &&
           (input[input_length - 1] == '\n' ||
            input[input_length - 1] == '\r')) {
        input[--input_length] = '\0';
    }

    if (count_substrings(input, &count) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}