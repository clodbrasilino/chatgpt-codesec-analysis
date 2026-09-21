#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

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

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            return ferror(stdin) ? 0 : 1;
        }
    }

    return 1;
}

static int read_line(char **line)
{
    char *buffer;
    char *newline;
    size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return 0;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     */
    } else if (strlen(buffer) > (size_t)MAX_INPUT_LENGTH) {
        if (!discard_line()) {
            free(buffer);
            return 0;
        }

        free(buffer);
        return 0;
    } else if (!feof(stdin)) {
        if (!discard_line()) {
            free(buffer);
            return 0;
        }

        free(buffer);
        return 0;
    }

    *line = buffer;
    return 1;
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
    char *input = NULL;
    char *cursor;
    long long first;
    long long second;
    long long sum;

    if (!read_line(&input)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_number(&cursor, &first)) {
        fputs("Invalid first number.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (!parse_number(&cursor, &second)) {
        fputs("Invalid second number.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Unexpected input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (!add_numbers(first, second, &sum)) {
        fputs("Integer overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %lld\nDigits: %u\n", sum, count_digits(sum)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}