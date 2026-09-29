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

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

static int read_long(const char *prompt, long *value)
{
    char *buffer = NULL;
    size_t capacity = 128;
    size_t length = 0;
    char *end;
    long parsed;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                discard_line();
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                discard_line();
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtol(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        free(buffer);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = parsed;
    free(buffer);
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

static char *make_prompt(size_t index)
{
    int length;
    char *prompt;

    length = snprintf(NULL, 0, "Enter value %zu: ", index);
    if (length < 0) {
        return NULL;
    }

    if ((size_t)length == SIZE_MAX) {
        return NULL;
    }

    prompt = malloc((size_t)length + 1);
    if (prompt == NULL) {
        return NULL;
    }

    if (snprintf(prompt, (size_t)length + 1,
                 "Enter value %zu: ", index) != length) {
        free(prompt);
        return NULL;
    }

    return prompt;
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
        char *prompt = make_prompt(i + 1);

        if (prompt == NULL) {
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