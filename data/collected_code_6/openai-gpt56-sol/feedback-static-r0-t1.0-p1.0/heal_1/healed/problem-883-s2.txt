#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_divisible_by_both(int value, int m, int n)
{
    return m != 0 && n != 0 && value % m == 0 && value % n == 0;
}

static int read_int(const char *prompt, int *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end;
    long parsed;
    ssize_t length;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtol(line, &end, 10);

    if (errno == ERANGE || end == line || parsed < INT_MIN || parsed > INT_MAX) {
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

    *value = (int)parsed;
    free(line);
    return 1;
}

static size_t find_divisible_numbers(const int *numbers,
                                     size_t count,
                                     int m,
                                     int n,
                                     int *results,
                                     size_t capacity)
{
    size_t found = 0;

    if (numbers == NULL || results == NULL || m == 0 || n == 0) {
        return 0;
    }

    for (size_t i = 0; i < count && found < capacity; ++i) {
        if (is_divisible_by_both(numbers[i], m, n)) {
            results[found++] = numbers[i];
        }
    }

    return found;
}

int main(void)
{
    int count_input;
    int m;
    int n;
    int *numbers = NULL;
    int *results = NULL;
    size_t count;
    size_t found;
    int status = EXIT_FAILURE;

    if (!read_int("Enter the number of values: ", &count_input) ||
        count_input <= 0) {
        fputs("Invalid number of values.\n", stderr);
        return EXIT_FAILURE;
    }

    count = (size_t)count_input;

    if (count > SIZE_MAX / sizeof *numbers) {
        fputs("Input size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof *numbers);
    results = malloc(count * sizeof *results);

    if (numbers == NULL || results == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        goto cleanup;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("Enter value %zu: ", i + 1) < 0 ||
            fflush(stdout) == EOF ||
            !read_int("", &numbers[i])) {
            fputs("Invalid value.\n", stderr);
            goto cleanup;
        }
    }

    if (!read_int("Enter m: ", &m) || m == 0) {
        fputs("m must be a nonzero integer.\n", stderr);
        goto cleanup;
    }

    if (!read_int("Enter n: ", &n) || n == 0) {
        fputs("n must be a nonzero integer.\n", stderr);
        goto cleanup;
    }

    found = find_divisible_numbers(numbers, count, m, n, results, count);

    if (found == 0) {
        puts("No matching numbers found.");
    } else {
        puts("Numbers divisible by both m and n:");
        for (size_t i = 0; i < found; ++i) {
            printf("%d\n", results[i]);
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(results);
    free(numbers);
    return status;
}