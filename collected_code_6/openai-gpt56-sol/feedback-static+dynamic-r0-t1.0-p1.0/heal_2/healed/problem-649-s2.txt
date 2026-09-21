#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

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

int main(void)
{
    static const int numbers[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    char input[256];
    size_t start;
    size_t end;
    int64_t result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t input_length = strlen(input);

    if (input_length > 0 && input[input_length - 1] == '\n') {
        input[input_length - 1] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_indices(input, &start, &end) != 0) {
        fputs("Enter two valid indices.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_range(numbers, length, start, end, &result) != 0) {
        fputs("Invalid range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    return EXIT_SUCCESS;
}