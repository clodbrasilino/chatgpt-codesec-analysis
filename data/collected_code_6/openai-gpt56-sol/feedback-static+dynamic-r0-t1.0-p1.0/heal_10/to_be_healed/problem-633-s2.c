#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity == 0) {
        size_t initial_capacity = 64;
        char *buffer = malloc(initial_capacity);

        if (buffer == NULL) {
            return -1;
        }

        *line = buffer;
        *capacity = initial_capacity;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return -1;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            return -1;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = *capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    (*line)[length] = '\0';
    return 0;
}

static int trailing_space_only(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text == ' ' || *text == '\t' || *text == '\n' ||
           *text == '\r' || *text == '\f' || *text == '\v') {
        ++text;
    }

    return *text == '\0';
}

static int parse_uintmax_line(uintmax_t maximum, uintmax_t *value)
{
    char *line = NULL;
    char *end = NULL;
    size_t capacity = 0;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL) {
        return -1;
    }

    if (read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (end != line &&
        line[0] != '-' &&
        errno != ERANGE &&
        parsed <= maximum &&
        trailing_space_only(end)) {
        *value = parsed;
        status = 0;
    }

    free(line);
    return status;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        parse_uintmax_line((uintmax_t)SIZE_MAX, &parsed) != 0) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        parse_uintmax_line((uintmax_t)UINT64_MAX, &parsed) != 0) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

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

    free(array);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}