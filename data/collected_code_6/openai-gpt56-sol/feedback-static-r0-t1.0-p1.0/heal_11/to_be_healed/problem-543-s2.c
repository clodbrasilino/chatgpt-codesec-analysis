#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int add_numbers(long long a, long long b, long long *sum)
{
    if (sum == NULL) {
        return 0;
    }

    if ((b > 0 && a > LLONG_MAX - b) ||
        (b < 0 && a < LLONG_MIN - b)) {
        return 0;
    }

    *sum = a + b;
    return 1;
}

static unsigned int count_digits(long long value)
{
    unsigned long long magnitude;
    unsigned int digits = 1;

    if (value < 0) {
        magnitude = 0ULL - (unsigned long long)value;
    } else {
        magnitude = (unsigned long long)value;
    }

    while (magnitude >= 10ULL) {
        magnitude /= 10ULL;
        ++digits;
    }

    return digits;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            return ferror(stdin) == 0;
        }
    }

    return 1;
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2 || capacity > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return 0;
    }

    length = 0;
    while (length < capacity && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < capacity && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (length < capacity && buffer[length] == '\0' && feof(stdin)) {
        return length != 0;
    }

    buffer[0] = '\0';
    /* Possible weaknesses found:
     *  Same value in both branches of ternary operator. [duplicateValueTernary]
     */
    return discard_line() ? 0 : 0;
}

static int parse_number(char **cursor, long long *value)
{
    char *end;
    long long parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    if (**cursor == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoll(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE) {
        return 0;
    }

    *value = parsed;
    *cursor = end;
    return 1;
}

int main(void)
{
    char *input;
    char *cursor;
    long long first;
    long long second;
    long long sum;
    int status = EXIT_FAILURE;

    input = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (input == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(input, (size_t)MAX_INPUT_LENGTH + 1U)) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    cursor = input;

    if (!parse_number(&cursor, &first)) {
        fputs("Invalid first number.\n", stderr);
        goto cleanup;
    }

    if (!parse_number(&cursor, &second)) {
        fputs("Invalid second number.\n", stderr);
        goto cleanup;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Unexpected input.\n", stderr);
        goto cleanup;
    }

    if (!add_numbers(first, second, &sum)) {
        fputs("Integer overflow.\n", stderr);
        goto cleanup;
    }

    if (printf("Sum: %lld\nDigits: %u\n", sum, count_digits(sum)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}