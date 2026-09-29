#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const unsigned char *str, size_t length,
                            uint64_t *result)
{
    uint64_t frequencies[UINT8_MAX + 1] = {0};
    uint64_t total = 0;

    if (result == NULL || (str == NULL && length != 0)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        uint64_t frequency = frequencies[str[i]];

        if (frequency == UINT64_MAX) {
            return -1;
        }

        uint64_t increment = frequency + UINT64_C(1);

        if (total > UINT64_MAX - increment) {
            return -1;
        }

        total += increment;
        frequencies[str[i]] = increment;
    }

    *result = total;
    return 0;
}

static int read_line(FILE *stream, unsigned char **buffer, size_t *length)
{
    unsigned char *data = NULL;
    size_t used = 0;
    size_t capacity = 128;

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
        int ch;

        if (used == capacity) {
            size_t new_capacity;
            unsigned char *new_data;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2;
            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return -1;
            }

            data = new_data;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(data);
                return -1;
            }
            break;
        }

        data[used++] = (unsigned char)ch;
    }

    if (used > 0 && data[used - 1] == '\r') {
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
    uint64_t result = 0;

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