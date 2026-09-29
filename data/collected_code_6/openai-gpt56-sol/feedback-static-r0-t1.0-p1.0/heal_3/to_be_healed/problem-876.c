#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm(uintmax_t a, uintmax_t b, uintmax_t *result)
{
    uintmax_t divisor;

    if (a == 0 || b == 0 || result == NULL) {
        return -1;
    }

    divisor = gcd(a, b);

    if (a / divisor > UINTMAX_MAX / b) {
        return -1;
    }

    *result = (a / divisor) * b;
    return 0;
}

static int parse_uintmax(const char **input, uintmax_t *value)
{
    const char *start;
    char *end;

    if (input == NULL || *input == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    start = *input;

    if (*start == '\0' || *start == '-' || *start == '+') {
        return -1;
    }

    errno = 0;
    *value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        return -1;
    }

    *input = end;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    const char *cursor;
    uintmax_t a;
    uintmax_t b;
    uintmax_t result;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(input);
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fprintf(stderr, "Invalid input\n");
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fprintf(stderr, "Memory allocation failed\n");
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';
    cursor = input;

    if (parse_uintmax(&cursor, &a) != 0 ||
        parse_uintmax(&cursor, &b) != 0) {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || a == 0 || b == 0) {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (lcm(a, b, &result) != 0) {
        free(input);
        fprintf(stderr, "LCM cannot be represented\n");
        return EXIT_FAILURE;
    }

    free(input);
    printf("%" PRIuMAX "\n", result);
    return EXIT_SUCCESS;
}