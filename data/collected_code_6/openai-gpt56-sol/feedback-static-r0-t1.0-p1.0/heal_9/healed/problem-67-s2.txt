#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int bell_number(size_t n, uint64_t *result)
{
    uint64_t *row;

    if (result == NULL || n == SIZE_MAX ||
        n + 1 > SIZE_MAX / sizeof(*row)) {
        return -1;
    }

    row = calloc(n + 1, sizeof(*row));
    if (row == NULL) {
        return -1;
    }

    row[0] = 1;

    for (size_t i = 1; i <= n; ++i) {
        uint64_t previous = row[0];

        row[0] = row[i - 1];

        for (size_t j = 1; j <= i; ++j) {
            uint64_t current = row[j];

            if (previous > UINT64_MAX - row[j - 1]) {
                free(row);
                return -2;
            }

            row[j] = row[j - 1] + previous;
            previous = current;
        }
    }

    *result = row[0];
    free(row);
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -2;
            }

            if (length == 0) {
                free(buffer);
                return -3;
            }

            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    uintmax_t value;
    uint64_t result;
    int status;

    status = read_line(stdin, &input);
    if (status != 0) {
        if (status == -1) {
            fputs("Memory allocation failed.\n", stderr);
        } else {
            fputs("Failed to read input.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value > SIZE_MAX) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    status = bell_number((size_t)value, &result);
    if (status == -1) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == -2) {
        fputs("Bell number exceeds uint64_t range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}