#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int arithmetic_term(int64_t first, int64_t difference, int64_t term,
                           int64_t *result)
{
    int64_t steps;

    if (result == NULL || term < 1) {
        return 0;
    }

    steps = term - 1;

    if (difference > 0 && steps > (INT64_MAX - first) / difference) {
        return 0;
    }

    if (difference < 0) {
        uint64_t magnitude = (uint64_t)(-(difference + 1)) + UINT64_C(1);
        uint64_t distance = (uint64_t)first - (uint64_t)INT64_MIN;

        if ((uint64_t)steps > distance / magnitude) {
            return 0;
        }
    }

    *result = first + steps * difference;
    return 1;
}

static int is_space_char(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int parse_int64(const char **input, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (is_space_char(**input)) {
        ++*input;
    }

    if (**input == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*input, &end, 10);

    if (end == *input || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    *input = end;
    return 1;
}

static char *read_input(void)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        char chunk[256];

        if (fgets(chunk, sizeof chunk, stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        size_t chunk_length = 0;

        while (chunk_length < sizeof chunk && chunk[chunk_length] != '\0' &&
               chunk[chunk_length] != '\n') {
            ++chunk_length;
        }

        if (chunk_length > SIZE_MAX - length - 1) {
            free(buffer);
            return NULL;
        }

        size_t required = length + chunk_length + 1;

        if (required > capacity) {
            size_t new_capacity = capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        for (size_t i = 0; i < chunk_length; ++i) {
            buffer[length + i] = chunk[i];
        }

        length += chunk_length;
        buffer[length] = '\0';

        if (chunk[chunk_length] == '\n') {
            break;
        }

        if (chunk_length < sizeof chunk - 1) {
            break;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *buffer = read_input();
    const char *input;
    int64_t first;
    int64_t difference;
    int64_t term;
    int64_t result;

    if (buffer == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    input = buffer;

    if (!parse_int64(&input, &first) ||
        !parse_int64(&input, &difference) ||
        !parse_int64(&input, &term)) {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_char(*input)) {
        ++input;
    }

    if (*input != '\0') {
        free(buffer);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(buffer);

    if (!arithmetic_term(first, difference, term, &result)) {
        fputs("Invalid term or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}