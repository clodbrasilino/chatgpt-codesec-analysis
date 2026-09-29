#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

static int count_substrings(const unsigned char *str, uint64_t *result)
{
    uint64_t frequencies[UCHAR_MAX + 1U] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    while (*str != '\0') {
        uint64_t frequency = frequencies[*str];

        if (frequency == UINT64_MAX ||
            total == UINT64_MAX ||
            frequency > UINT64_MAX - total - UINT64_C(1)) {
            return -1;
        }

        total += frequency + UINT64_C(1);
        frequencies[*str] = frequency + UINT64_C(1);
        ++str;
    }

    *result = total;
    return 0;
}

static int read_line(FILE *stream, unsigned char **buffer)
{
    unsigned char *data;
    size_t capacity = 64U;
    size_t length = 0U;

    if (stream == NULL || buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    data = malloc(capacity);

    if (data == NULL) {
        return -1;
    }

    for (;;) {
        int character;

        if (length == capacity - 1U) {
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

        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(data);
                return -1;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        data[length++] = (unsigned char)character;
    }

    data[length] = '\0';
    *buffer = data;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    uint64_t count;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input) != 0) {
        goto cleanup;
    }

    if (count_substrings(input, &count) != 0) {
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