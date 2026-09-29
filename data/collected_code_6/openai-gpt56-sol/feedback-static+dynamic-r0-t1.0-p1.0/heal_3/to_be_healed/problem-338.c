#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const char *str, size_t length, uint64_t *result)
{
    uint64_t frequencies[UINT8_MAX + 1] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char c = (unsigned char)str[i];

        if (frequencies[c] == UINT64_MAX) {
            return -1;
        }

        uint64_t increment = frequencies[c] + UINT64_C(1);

        if (total > UINT64_MAX - increment) {
            return -1;
        }

        total += increment;
        ++frequencies[c];
    }

    *result = total;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data = NULL;
    size_t used = 0;
    size_t capacity = 0;
    int ch;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (used == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity || new_capacity > SIZE_MAX) {
                free(data);
                return -1;
            }

            char *new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return -1;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used++] = (char)(unsigned char)ch;
    }

    if (ferror(stream) || (ch == EOF && used == 0)) {
        free(data);
        return -1;
    }

    if (used > 0 && data[used - 1] == '\r') {
        --used;
    }

    if (data == NULL) {
        data = malloc(1);
        if (data == NULL) {
            return -1;
        }
    }

    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
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