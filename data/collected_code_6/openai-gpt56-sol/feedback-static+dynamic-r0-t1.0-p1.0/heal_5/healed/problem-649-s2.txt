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
    enum { MAX_INPUT_LENGTH = 4096 };
    char *buffer;
    size_t length;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc((size_t)MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        free(buffer);
        return -1;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        free(buffer);
        return -1;
    } else if (!feof(stdin)) {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            free(buffer);
            return -1;
        }

        if (ch == EOF && ferror(stdin)) {
            free(buffer);
            return -1;
        }
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

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