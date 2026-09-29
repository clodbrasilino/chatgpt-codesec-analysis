#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int bell_number(size_t n, uint64_t *result)
{
    uint64_t *row;

    if (result == NULL || n == SIZE_MAX ||
        n + 1U > SIZE_MAX / sizeof(*row)) {
        return -1;
    }

    row = calloc(n + 1U, sizeof(*row));
    if (row == NULL) {
        return -1;
    }

    row[0] = UINT64_C(1);

    for (size_t i = 1U; i <= n; ++i) {
        row[i] = row[0];

        for (size_t j = i; j > 0U; --j) {
            if (row[j - 1U] > UINT64_MAX - row[j]) {
                free(row);
                return -1;
            }

            row[j - 1U] += row[j];
        }
    }

    *result = row[0];
    free(row);
    return 0;
}

static int read_line(char **line, size_t *length)
{
    char *buffer = NULL;
    size_t capacity = 0U;
    size_t used = 0U;
    int ch;

    if (line == NULL || length == NULL) {
        return -1;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(buffer);
                    return -1;
                }

                new_capacity = capacity * 2U;
            }

            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return -1;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (buffer == NULL) {
        buffer = malloc(1U);
        if (buffer == NULL) {
            return -1;
        }
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *input;
    char *end;
    size_t length;
    uintmax_t value;
    uint64_t result;

    if (read_line(&input, &length) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0U || input[0] == '-') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value > SIZE_MAX) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (bell_number((size_t)value, &result) != 0) {
        fputs("Bell number cannot be represented or computed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}