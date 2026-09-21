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
    /* Possible weaknesses found:
     *  Assuming that condition 'left==0' is not redundant
     *  Assuming that condition 'right==0' is not redundant
     */
    if (left == 0 || right == 0) {
        *result = 0;
        return 1;
    }

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if ((left == INT64_MIN && right == -1) ||
        (right == INT64_MIN && left == -1)) {
        return 0;
    }

    if (left > 0) {
        if (right > 0) {
            if (left > INT64_MAX / right) {
                return 0;
            }
        } else if (right < INT64_MIN / left) {
            return 0;
        }
    /* Possible weaknesses found:
     *  Condition 'left<0' is always true [knownConditionTrueFalse]
     *  Condition 'left<0' is always true
     */
    } else if (left < 0) {
        if (right > 0) {
            if (left < INT64_MIN / right) {
                return 0;
            }
        /* Possible weaknesses found:
         *  Condition 'right<0' is always true
         *  Condition 'right<0' is always true [knownConditionTrueFalse]
         */
        } else if (right < 0 && left < INT64_MAX / right) {
            return 0;
        }
    }

    *result = left * right;
    return 1;
#endif
}

static int parse_int64(const char **input, int64_t *value)
{
    const char *start;
    char *end;
    intmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    start = *input;

    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    *input = end;
    return 1;
}

static int read_line(FILE *stream, char **buffer)
{
    size_t capacity = 128;
    size_t length = 0;
    char *data;

    if (stream == NULL || buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    data = malloc(capacity);

    if (data == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(data);
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(data);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                free(data);
                return 0;
            }

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

    data[length] = '\0';
    *buffer = data;
    return 1;
}

int main(void)
{
    char *input = NULL;
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

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
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