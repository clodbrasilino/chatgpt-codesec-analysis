#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_int64(int64_t a, int64_t b, int64_t *sum)
{
    if (sum == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *sum = a + b;
    return 1;
}

static size_t digit_count(int64_t value)
{
    uint64_t magnitude;
    size_t count = 1U;

    if (value < 0) {
        magnitude = (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)value;
    }

    while (magnitude >= UINT64_C(10)) {
        magnitude /= UINT64_C(10);
        ++count;
    }

    return count;
}

static int read_line(char **line)
{
    size_t length = 0U;
    size_t capacity = 64U;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return 0;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length + 1U) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static void skip_space(const char **input)
{
    while (**input != '\0' &&
           isspace((unsigned char)**input) != 0) {
        ++*input;
    }
}

static int parse_int64(const char **input, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    skip_space(input);

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

int main(void)
{
    char *input;
    const char *cursor;
    int64_t first;
    int64_t second;
    int64_t sum;

    if (fputs("Enter two integers: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(&input)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_int64(&cursor, &first) ||
        !parse_int64(&cursor, &second)) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    skip_space(&cursor);

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!add_int64(first, second, &sum)) {
        fputs("Integer overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRId64 "\nDigits: %zu\n",
               sum, digit_count(sum)) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}