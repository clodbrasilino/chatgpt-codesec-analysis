#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

static int count_substrings(const unsigned char *str, size_t length,
                            uint64_t *result)
{
    uint64_t frequencies[UCHAR_MAX + 1U] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        uint64_t frequency = frequencies[str[i]];

        if (frequency == UINT64_MAX ||
            total == UINT64_MAX ||
            frequency > UINT64_MAX - total - UINT64_C(1)) {
            return -1;
        }

        total += frequency + UINT64_C(1);
        frequencies[str[i]] = frequency + UINT64_C(1);
    }

    *result = total;
    return 0;
}

static int read_line(unsigned char **buffer, size_t *length)
{
    unsigned char *data;
    size_t capacity = 64U;
    size_t used = 0U;
    int character;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0U;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (used == capacity - 1U) {
            size_t new_capacity;
            unsigned char *temporary;

            if (capacity > SIZE_MAX / 2U) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2U;
            temporary = realloc(data, new_capacity);
            if (temporary == NULL) {
                free(data);
                return -1;
            }

            data = temporary;
            capacity = new_capacity;
        }

        data[used++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(data);
        return -1;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;
    uint64_t count;
    int status = EXIT_FAILURE;

    if (read_line(&input, &length) != 0) {
        goto cleanup;
    }

    if (count_substrings(input, length, &count) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}