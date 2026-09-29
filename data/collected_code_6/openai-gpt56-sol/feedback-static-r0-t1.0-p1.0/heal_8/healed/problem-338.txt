#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const unsigned char *str, size_t length,
                            uint64_t *result)
{
    uint64_t frequencies[UINT8_MAX + 1U] = {0};
    uint64_t total = 0;

    if (result == NULL || (str == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        const unsigned int c = str[i];

        if (frequencies[c] == UINT64_MAX) {
            return -1;
        }

        const uint64_t increment = frequencies[c] + UINT64_C(1);

        if (total > UINT64_MAX - increment) {
            return -1;
        }

        frequencies[c] = increment;
        total += increment;
    }

    *result = total;
    return 0;
}

static int read_line(FILE *stream, unsigned char **buffer, size_t *length)
{
    unsigned char *data;
    size_t used = 0;
    size_t capacity = 256U;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) != 0 || used == 0U) {
                free(data);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            unsigned char *new_data;

            if (capacity > SIZE_MAX / 2U) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return -1;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used++] = (unsigned char)ch;
    }

    if (used > 0U && data[used - 1U] == (unsigned char)'\r') {
        --used;
    }

    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    uint64_t result;

    if (read_line(stdin, &input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (count_substrings(input, length, &result) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}