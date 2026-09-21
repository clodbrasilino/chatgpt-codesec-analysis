#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_long(const char *prompt, long *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end;
    long parsed;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    errno = 0;
    {
        ssize_t length = getline(&line, &capacity, stdin);

        if (length < 0) {
            free(line);
            return 0;
        }
    }

    errno = 0;
    parsed = strtol(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    ch = ferror(stdin);
    free(line);

    if (ch) {
        return 0;
    }

    *value = parsed;
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

static void print_divisible_numbers(const long numbers[], size_t count,
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
        (uintmax_t)count_input > SIZE_MAX / sizeof *numbers) {
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

    if (count != 0) {
        numbers = malloc(count * sizeof *numbers);
        if (numbers == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            goto cleanup;
        }
    }

    for (i = 0; i < count; ++i) {
        if (printf("Enter value %zu: ", i + 1) < 0 ||
            fflush(stdout) == EOF ||
            !read_long("", &numbers[i])) {
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