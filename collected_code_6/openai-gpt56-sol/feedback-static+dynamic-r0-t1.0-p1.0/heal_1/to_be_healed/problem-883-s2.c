#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int is_divisible_by_both(int value, int m, int n)
{
    return m != 0 && n != 0 && value % m == 0 && value % n == 0;
}

static int read_int(const char *prompt, int *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end = NULL;
    long parsed;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    fputs(prompt, stdout);
    if (fflush(stdout) == EOF || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtol(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static size_t find_divisible_numbers(const int numbers[],
                                     size_t count,
                                     int m,
                                     int n,
                                     int results[],
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
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char prompt[64];
        int written = snprintf(prompt, sizeof prompt, "Enter value %zu: ", i + 1);

        if (written < 0 || (size_t)written >= sizeof prompt ||
            !read_int(prompt, &numbers[i])) {
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