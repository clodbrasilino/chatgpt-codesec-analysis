#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_substrings(const char *digits, uint64_t *result)
{
    size_t length;
    size_t table_size;
    uint64_t *frequencies;
    int64_t prefix = 0;
    uint64_t count = 0;

    if (digits == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(digits);

    if (length > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    table_size = (length * 2U) + 1U;

    if (table_size > SIZE_MAX / sizeof(*frequencies)) {
        return -1;
    }

    frequencies = calloc(table_size, sizeof(*frequencies));
    if (frequencies == NULL) {
        return -1;
    }

    frequencies[length] = 1U;

    for (size_t i = 0; i < length; ++i) {
        int64_t transformed;
        size_t index;

        if (!isdigit((unsigned char)digits[i])) {
            free(frequencies);
            return -1;
        }

        prefix += (int64_t)(digits[i] - '0') - 1;
        transformed = prefix + (int64_t)length;

        if (transformed < 0 || (uint64_t)transformed >= (uint64_t)table_size) {
            free(frequencies);
            return -1;
        }

        index = (size_t)transformed;

        if (UINT64_MAX - count < frequencies[index]) {
            free(frequencies);
            return -1;
        }

        count += frequencies[index];

        if (frequencies[index] == UINT64_MAX) {
            free(frequencies);
            return -1;
        }

        ++frequencies[index];
    }

    free(frequencies);
    *result = count;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    uint64_t result;

    errno = 0;
    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    if (count_substrings(input, &result) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}