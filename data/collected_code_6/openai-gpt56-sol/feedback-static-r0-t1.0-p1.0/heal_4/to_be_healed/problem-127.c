#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int multiply_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

#if defined(__GNUC__) || defined(__clang__)
    return !__builtin_mul_overflow(left, right, result);
#else
    if (left > 0) {
        if ((right > 0 && left > INT64_MAX / right) ||
            (right < 0 && right < INT64_MIN / left)) {
            return 0;
        }
    } else if (left < 0) {
        if ((right > 0 && left < INT64_MIN / right) ||
            (right < 0 && left < INT64_MAX / right)) {
            return 0;
        }
    }

    *result = left * right;
    return 1;
#endif
}

static int parse_int64(const char **input, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
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

static int read_line(FILE *stream, char **buffer)
{
    char *data;
    size_t capacity = 128;
    size_t length = 0;
    int character;

    if (stream == NULL || buffer == NULL) {
        return 0;
    }

    data = malloc(capacity);
    if (data == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        if (length == SIZE_MAX - 1) {
            free(data);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(data, new_capacity);
            if (resized == NULL) {
                free(data);
                return 0;
            }

            data = resized;
            capacity = new_capacity;
        }

        data[length++] = (char)character;

        if (character == '\n') {
            break;
        }
    }

    if (ferror(stream) || (character == EOF && length == 0)) {
        free(data);
        return 0;
    }

    data[length] = '\0';
    *buffer = data;
    return 1;
}

int main(void)
{
    char *input;
    const char *cursor;
    int64_t left;
    int64_t right;
    int64_t result;

    if (!read_line(stdin, &input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_int64(&cursor, &left) ||
        !parse_int64(&cursor, &right)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!multiply_int64(left, right, &result)) {
        fputs("Multiplication overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}