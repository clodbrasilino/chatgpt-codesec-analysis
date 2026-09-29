#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int sum_range(const int *numbers, size_t length, size_t start,
                     size_t end, int64_t *result)
{
    int64_t sum = 0;

    if (numbers == NULL || result == NULL || length == 0 ||
        start > end || end >= length) {
        return -1;
    }

    for (size_t i = start; i <= end; ++i) {
        sum += numbers[i];
    }

    *result = sum;
    return 0;
}

static int parse_indices(const char *input, size_t *start, size_t *end)
{
    const char *cursor;
    char *next;
    uintmax_t first;
    uintmax_t second;

    if (input == NULL || start == NULL || end == NULL) {
        return -1;
    }

    cursor = input;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return -1;
    }

    errno = 0;
    first = strtoumax(cursor, &next, 10);
    if (next == cursor || errno == ERANGE || first > SIZE_MAX) {
        return -1;
    }

    cursor = next;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return -1;
    }

    errno = 0;
    second = strtoumax(cursor, &next, 10);
    if (next == cursor || errno == ERANGE || second > SIZE_MAX) {
        return -1;
    }

    cursor = next;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return -1;
    }

    *start = (size_t)first;
    *end = (size_t)second;
    return 0;
}

static int read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
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
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    static const int numbers[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    char *input = NULL;
    size_t start;
    size_t end;
    int64_t result;

    if (read_line(&input) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_indices(input, &start, &end) != 0) {
        free(input);
        fputs("Enter two valid indices.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (sum_range(numbers, length, start, end, &result) != 0) {
        fputs("Invalid range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}