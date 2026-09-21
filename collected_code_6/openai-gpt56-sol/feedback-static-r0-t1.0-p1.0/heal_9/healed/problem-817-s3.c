#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || feof(stdin);
}

static int read_long(const char *prompt, long *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    long parsed;
    int ch;
    int result = 0;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                goto cleanup;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            discard_line();
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    discard_line();
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                discard_line();
                goto cleanup;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (length + 1 > capacity) {
        char *new_line = realloc(line, length + 1);

        if (new_line == NULL) {
            goto cleanup;
        }

        line = new_line;
        capacity = length + 1;
    }

    line[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtol(line, &end, 10);

    if (errno == ERANGE || end == line) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = parsed;
    result = 1;

cleanup:
    free(line);
    return result;
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

static int print_divisible_numbers(const long *numbers, size_t count,
                                   long m, long n)
{
    size_t i;
    int found = 0;

    if (count != 0 && numbers == NULL) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (is_divisible_by(numbers[i], m) ||
            is_divisible_by(numbers[i], n)) {
            if (printf("%ld\n", numbers[i]) < 0) {
                return 0;
            }
            found = 1;
        }
    }

    if (!found && puts("No matching numbers.") == EOF) {
        return 0;
    }

    return 1;
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
        (uintmax_t)count_input >
            (uintmax_t)(SIZE_MAX / sizeof *numbers)) {
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
        char *prompt;
        int required;

        required = snprintf(NULL, 0, "Enter value %zu: ", i + 1);
        if (required < 0 || (size_t)required == SIZE_MAX) {
            fputs("Unable to create input prompt.\n", stderr);
            goto cleanup;
        }

        prompt = malloc((size_t)required + 1);
        if (prompt == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            goto cleanup;
        }

        if (snprintf(prompt, (size_t)required + 1,
                     "Enter value %zu: ", i + 1) != required) {
            free(prompt);
            fputs("Unable to create input prompt.\n", stderr);
            goto cleanup;
        }

        if (!read_long(prompt, &numbers[i])) {
            free(prompt);
            fputs("Invalid value.\n", stderr);
            goto cleanup;
        }

        free(prompt);
    }

    if (!print_divisible_numbers(numbers, count, m, n)) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(numbers);
    return status;
}