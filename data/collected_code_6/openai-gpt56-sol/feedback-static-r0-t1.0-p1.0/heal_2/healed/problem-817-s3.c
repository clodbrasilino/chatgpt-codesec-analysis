#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_long(const char *prompt, long *value)
{
    char *line = NULL;
    char *end;
    long parsed;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(line);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return 0;
    }

    if (capacity <= length) {
        char *resized = realloc(line, length + 1);

        if (resized == NULL) {
            free(line);
            return 0;
        }

        line = resized;
    }

    line[length] = '\0';

    errno = 0;
    parsed = strtol(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
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

static int is_divisible_by(long value, long divisor)
{
    if (divisor == 0) {
        return 0;
    }

    if (value == LONG_MIN && divisor == -1) {
        return 1;
    }

    return value % divisor == 0;
}

static void print_divisible_numbers(const long *numbers, size_t count,
                                    long m, long n)
{
    size_t i;
    int found = 0;

    for (i = 0; i < count; ++i) {
        if (is_divisible_by(numbers[i], m) ||
            is_divisible_by(numbers[i], n)) {
            printf("%ld\n", numbers[i]);
            found = 1;
        }
    }

    if (!found) {
        puts("No matching numbers.");
    }
}

int main(void)
{
    long count_input;
    long m;
    long n;
    long *numbers = NULL;
    size_t count;
    size_t i;
    int status = EXIT_FAILURE;

    if (!read_long("Enter the number of values: ", &count_input) ||
        count_input < 0 ||
        (uintmax_t)count_input > (uintmax_t)(SIZE_MAX / sizeof *numbers)) {
        fputs("Invalid number of values.\n", stderr);
        goto cleanup;
    }

    count = (size_t)count_input;

    if (!read_long("Enter m: ", &m) ||
        !read_long("Enter n: ", &n) ||
        (m == 0 && n == 0)) {
        fputs("Invalid divisors.\n", stderr);
        goto cleanup;
    }

    if (count > 0) {
        numbers = malloc(count * sizeof *numbers);
        if (numbers == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            goto cleanup;
        }
    }

    for (i = 0; i < count; ++i) {
        char prompt[64];
        int written = snprintf(prompt, sizeof prompt,
                               "Enter value %zu: ", i + 1);

        if (written < 0 || (size_t)written >= sizeof prompt ||
            !read_long(prompt, &numbers[i])) {
            fputs("Invalid value.\n", stderr);
            goto cleanup;
        }
    }

    print_divisible_numbers(numbers, count, m, n);
    status = EXIT_SUCCESS;

cleanup:
    free(numbers);
    return status;
}