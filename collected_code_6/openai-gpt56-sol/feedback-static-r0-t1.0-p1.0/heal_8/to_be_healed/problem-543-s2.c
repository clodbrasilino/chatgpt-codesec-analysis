#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

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
    unsigned int digits = 1;
    unsigned long long magnitude;

    if (value < 0) {
        magnitude = (unsigned long long)(-(value + 1)) + 1ULL;
    } else {
        magnitude = (unsigned long long)value;
    }

    while (magnitude >= 10ULL) {
        magnitude /= 10ULL;
        ++digits;
    }

    return digits;
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;
    int ch;

    if (buffer == NULL || capacity < 2 || capacity > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return length <= MAX_INPUT_LENGTH;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(stdin);
    if (ch == '\n') {
        return length <= MAX_INPUT_LENGTH;
    }

    while (ch != '\n' && ch != EOF) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return 0;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH + 2];
    char *cursor;
    long long first;
    long long second;
    long long sum;

    if (!read_line(input, sizeof(input))) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_number(&cursor, &first)) {
        fputs("Invalid first number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_number(&cursor, &second)) {
        fputs("Invalid second number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Unexpected input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!add_numbers(first, second, &sum)) {
        fputs("Integer overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %lld\nDigits: %u\n", sum, count_digits(sum)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}