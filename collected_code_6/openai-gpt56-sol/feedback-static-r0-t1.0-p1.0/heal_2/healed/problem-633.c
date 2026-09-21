#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    if (value == NULL) {
        return -1;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof *line) {
                free(line);
                return -1;
            }

            char *new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return -1;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(line);
        return -1;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(line);
            return -1;
        }

        char *new_line = realloc(line, capacity + 1);
        if (new_line == NULL) {
            free(line);
            return -1;
        }

        line = new_line;
    }

    line[length] = '\0';

    char *end;
    errno = 0;
    uintmax_t parsed = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 0;
}

static int sum_pairwise_xor(const uint64_t *array, size_t length,
                            uint64_t *result)
{
    if (result == NULL || (length != 0 && array == NULL) ||
        length > UINT64_MAX) {
        return -1;
    }

    uint64_t sum = 0;
    uint64_t count = (uint64_t)length;

    for (unsigned int bit = 0; bit < 64; ++bit) {
        uint64_t ones = 0;

        for (size_t i = 0; i < length; ++i) {
            ones += (array[i] >> bit) & UINT64_C(1);
        }

        uint64_t zeros = count - ones;

        if (ones != 0 && zeros > UINT64_MAX / ones) {
            return -1;
        }

        uint64_t pairs = ones * zeros;

        if (pairs > (UINT64_MAX >> bit)) {
            return -1;
        }

        uint64_t contribution = pairs << bit;

        if (sum > UINT64_MAX - contribution) {
            return -1;
        }

        sum += contribution;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    uint64_t input_length;

    if (read_uint64(&input_length) != 0 ||
        input_length > SIZE_MAX ||
        input_length > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)input_length;
    uint64_t *array = NULL;

    if (length != 0) {
        array = malloc(length * sizeof *array);
        if (array == NULL) {
            fputs("Allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_uint64(&array[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    uint64_t result;

    if (sum_pairwise_xor(array, length, &result) != 0) {
        fputs("Result overflow\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}