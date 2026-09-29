#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    if (value >= 0) {
        return (uintmax_t)value;
    }

    return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
}

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != UINTMAX_C(0)) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_intmax(intmax_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_line;

            if (new_capacity <= capacity || new_capacity > SIZE_MAX - 1) {
                free(line);
                while (ch != '\n' && ch != EOF) {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    ch = fgetc(stdin);
                }
                return 0;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                while (ch != '\n' && ch != EOF) {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    ch = fgetc(stdin);
                }
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return 0;
    }

    if (length == capacity) {
        char *new_line;

        if (capacity == SIZE_MAX) {
            free(line);
            return 0;
        }

        new_line = realloc(line, capacity + 1);
        if (new_line == NULL) {
            free(line);
            return 0;
        }

        line = new_line;
    }

    line[length] = '\0';
    start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed;
    free(line);
    return 1;
}

int main(void)
{
    intmax_t first;
    intmax_t second;

    if (!read_intmax(&first) || !read_intmax(&second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n",
               gcd(magnitude(first), magnitude(second))) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}