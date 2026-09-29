#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

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

    if (length < size && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    if (length == 0U && feof(stdin)) {
        return -1;
    }

    if (!feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        buffer[0] = '\0';
        return -1;
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char *input;
    uint64_t lower;
    uint64_t upper;
    uint64_t divisor;
    uint64_t occurrences;
    int result = EXIT_FAILURE;

    input = malloc(INPUT_SIZE);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_line(input, INPUT_SIZE) != 0) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (parse_interval(input, &lower, &upper) != 0) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (find_max_occurring_divisor(lower, upper,
                                   &divisor, &occurrences) != 0) {
        fputs("Invalid interval\n", stderr);
        goto cleanup;
    }

    if (printf("Divisor: %" PRIu64 "\nOccurrences: %" PRIu64 "\n",
               divisor, occurrences) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(input);
    return result;
}