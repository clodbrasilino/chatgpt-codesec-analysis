#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

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

static int read_line(char **line)
{
    enum { INITIAL_CAPACITY = 64 };
    char *buffer;
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -3;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity - 1) {
            char *new_buffer;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -2;
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

    status = read_line(&input);
    if (status == -1) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }
    if (status == -2) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }
    if (status != 0) {
        fputs("Failed to read input.\n", stderr);
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

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}