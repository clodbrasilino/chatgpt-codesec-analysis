#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t modulus, int *error)
{
    uint64_t *values;
    uint64_t result;
    uint64_t i;
    uint64_t j;
    size_t count;

    *error = 0;

    if (modulus == 1U || r > n) {
        return 0U;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r > (uint64_t)(SIZE_MAX / sizeof(*values) - 1U)) {
        *error = ENOMEM;
        return 0U;
    }

    count = (size_t)r + 1U;
    values = calloc(count, sizeof(*values));
    if (values == NULL) {
        *error = ENOMEM;
        return 0U;
    }

    values[0] = 1U % modulus;

    for (i = 1U;; ++i) {
        uint64_t limit = i < r ? i : r;

        for (j = limit; j > 0U; --j) {
            values[j] = add_mod(values[j], values[j - 1U], modulus);
        }

        if (i == n) {
            break;
        }
    }

    result = values[r];
    free(values);
    return result;
}

static int parse_uint64(const char **text, uint64_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    while (isspace((unsigned char)**text)) {
        ++*text;
    }

    start = *text;
    if (*start == '\0' || *start == '+' || *start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *text = end;
    return 1;
}

static int read_line(char **line)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        size_t available;
        int read_size;

        if (length > SIZE_MAX - 2U) {
            free(buffer);
            return -1;
        }

        available = capacity - length;

        if (available < 2U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
            available = capacity - length;
        }

        read_size = available > (size_t)INT_MAX ? INT_MAX : (int)available;

        if (fgets(buffer + length, read_size, stdin) == NULL) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }

            if (length == 0U) {
                free(buffer);
                return 0;
            }

            buffer[length] = '\0';
            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            break;
        }

        if (feof(stdin)) {
            break;
        }
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    const char *cursor;
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    uint64_t result;
    int error;
    int read_status;

    read_status = read_line(&input);
    if (read_status <= 0) {
        fputs(read_status < 0
                  ? "Input or memory allocation failed\n"
                  : "Invalid input\n",
              stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &n) ||
        !parse_uint64(&cursor, &r) ||
        !parse_uint64(&cursor, &modulus)) {
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

    if (modulus == 0U) {
        fputs("Modulus must be nonzero\n", stderr);
        return EXIT_FAILURE;
    }

    result = ncr_mod(n, r, modulus, &error);
    if (error != 0) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}