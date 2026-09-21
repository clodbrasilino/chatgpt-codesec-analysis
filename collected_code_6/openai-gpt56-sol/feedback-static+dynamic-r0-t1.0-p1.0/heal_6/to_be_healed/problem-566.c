#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_digits(uintmax_t value, uintmax_t *result)
{
    uintmax_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    do {
        sum += value % UINTMAX_C(10);
        value /= UINTMAX_C(10);
    } while (value != 0);

    *result = sum;
    return 0;
}

static int read_line(char **buffer)
{
    size_t length = 0;
    size_t capacity = 64;
    int ch;
    char *line;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    line = malloc(capacity);

    if (line == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return -1;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);

            if (new_line == NULL) {
                free(line);
                return -1;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return -1;
    }

    line[length] = '\0';
    *buffer = line;
    return 0;
}

static int is_space_char(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

int main(void)
{
    char *input;
    char *end;
    const char *p;
    uintmax_t value;
    uintmax_t sum;
    int status = EXIT_FAILURE;

    if (read_line(&input) != 0) {
        return EXIT_FAILURE;
    }

    p = input;

    while (is_space_char(*p)) {
        ++p;
    }

    if (*p == '-') {
        goto cleanup;
    }

    errno = 0;
    value = strtoumax(p, &end, 10);

    if (errno == ERANGE || end == p) {
        goto cleanup;
    }

    while (is_space_char(*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    if (sum_digits(value, &sum) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIuMAX "\n", sum) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}