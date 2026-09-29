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

    for (unsigned int bit = 0; bit < 64; ++bit) {
        uint64_t ones = 0;

        for (size_t i = 0; i < length; ++i) {
            ones += (array[i] >> bit) & UINT64_C(1);
        }

        uint64_t zeros = (uint64_t)length - ones;

        if (ones != 0 && zeros > UINT64_MAX / ones) {
            return 0;
        }

        uint64_t differing_pairs = ones * zeros;

        if (differing_pairs > (UINT64_MAX >> bit)) {
            return 0;
        }

        uint64_t contribution = differing_pairs << bit;

        if (sum > UINT64_MAX - contribution) {
            return 0;
        }

        sum += contribution;
    }

    *result = sum;
    return 1;
}

static int read_line(char **buffer, size_t *capacity)
{
    size_t length = 0;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return 0;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            return 0;
        }

        if (*capacity < length + 2) {
            size_t required = length + 2;
            size_t new_capacity = *capacity;

            if (new_capacity == 0) {
                new_capacity = 128;
            }

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)(unsigned char)ch;
    }

    if (*capacity < length + 1) {
        size_t new_capacity = length + 1;
        char *new_buffer = realloc(*buffer, new_capacity);

        if (new_buffer == NULL) {
            return 0;
        }

        *buffer = new_buffer;
        *capacity = new_capacity;
    }

    (*buffer)[length] = '\0';
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || parsed > UINT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    uint64_t length_value;
    size_t length;
    uint64_t *array = NULL;
    uint64_t result;

    if (!read_line(&line, &capacity) ||
        !parse_uint64(line, &length_value) ||
        length_value > SIZE_MAX) {
        fputs("Invalid input\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    length = (size_t)length_value;

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Input is too large\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));

        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free(line);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (!read_line(&line, &capacity) ||
                !parse_uint64(line, &array[i])) {
                fputs("Invalid input\n", stderr);
                free(array);
                free(line);
                return EXIT_FAILURE;
            }
        }
    }

    free(line);

    if (!sum_pairwise_xor(array, length, &result)) {
        fputs("Result overflow\n", stderr);
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