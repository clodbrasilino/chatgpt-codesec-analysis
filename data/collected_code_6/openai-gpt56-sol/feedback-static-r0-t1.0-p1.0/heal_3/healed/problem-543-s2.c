#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>

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

static int read_line(char **line)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char *buffer;
    size_t length;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc((size_t)MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        free(buffer);
        return 0;
    }

    for (length = 0; buffer[length] != '\0' && buffer[length] != '\n'; ++length) {
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        free(buffer);
        return 0;
    }

    *line = buffer;
    return 1;
}

static int parse_number(char **cursor, long long *value)
{
    char *end;

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
    *value = strtoll(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE) {
        return 0;
    }

    *cursor = end;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *cursor;
    long long first;
    long long second;
    long long sum;

    if (!read_line(&input)) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_number(&cursor, &first)) {
        fprintf(stderr, "Invalid first number.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (!parse_number(&cursor, &second)) {
        fprintf(stderr, "Invalid second number.\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fprintf(stderr, "Unexpected input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (!add_numbers(first, second, &sum)) {
        fprintf(stderr, "Integer overflow.\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum: %lld\nDigits: %u\n", sum, count_digits(sum)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}