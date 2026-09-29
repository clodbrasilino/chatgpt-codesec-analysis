#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define INPUT_SIZE 256U

static uint64_t divisor_occurrences(uint64_t divisor, uint64_t lower,
                                    uint64_t upper)
{
    return upper / divisor - (lower - 1U) / divisor;
}

static int find_max_occurring_divisor(uint64_t lower, uint64_t upper,
                                      uint64_t *divisor,
                                      uint64_t *occurrences)
{
    if (divisor == NULL || occurrences == NULL ||
        lower == 0U || lower > upper) {
        return -1;
    }

    *divisor = 1U;
    *occurrences = divisor_occurrences(*divisor, lower, upper);
    return 0;
}

static int parse_interval(const char *input, uint64_t *lower, uint64_t *upper)
{
    const char *cursor;
    char *end;
    uintmax_t first;
    uintmax_t second;

    if (input == NULL || lower == NULL || upper == NULL) {
        return -1;
    }

    cursor = input;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-') {
        return -1;
    }

    errno = 0;
    first = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || first > UINT64_MAX) {
        return -1;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-') {
        return -1;
    }

    errno = 0;
    second = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || second > UINT64_MAX) {
        return -1;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return -1;
    }

    *lower = (uint64_t)first;
    *upper = (uint64_t)second;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2U) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    length = 0U;
    while (length < size && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == size) {
        return -1;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    ch = fgetc(stdin);
    if (ch == '\n' || ch == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return -1;
}

int main(void)
{
    char input[INPUT_SIZE];
    uint64_t lower;
    uint64_t upper;
    uint64_t divisor;
    uint64_t occurrences;

    if (read_line(input, sizeof input) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_interval(input, &lower, &upper) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_max_occurring_divisor(lower, upper,
                                   &divisor, &occurrences) != 0) {
        fputs("Invalid interval\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Divisor: %" PRIu64 "\nOccurrences: %" PRIu64 "\n",
               divisor, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}