#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 256U

static int trapezium_median(double base1, double base2, double *median)
{
    double result;

    if (median == NULL ||
        !isfinite(base1) ||
        !isfinite(base2) ||
        base1 <= 0.0 ||
        base2 <= 0.0) {
        return 0;
    }

    result = base1 / 2.0 + base2 / 2.0;

    if (!isfinite(result)) {
        return 0;
    }

    *median = result;
    return 1;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    length = 0U;
    while (length < capacity && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == capacity) {
        return 0;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    if (!discard_line()) {
        return 0;
    }

    return 0;
}

static int read_positive_double(const char *prompt, double *value)
{
    char *buffer;
    char *end;
    double parsed;
    int success;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    buffer = malloc(INPUT_BUFFER_SIZE);
    if (buffer == NULL) {
        return 0;
    }

    success = 0;

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    if (!read_line(buffer, INPUT_BUFFER_SIZE)) {
        goto cleanup;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed <= 0.0) {
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = parsed;
    success = 1;

cleanup:
    free(buffer);
    return success;
}

int main(void)
{
    double base1;
    double base2;
    double median;

    if (!read_positive_double("Enter the first base: ", &base1) ||
        !read_positive_double("Enter the second base: ", &base2)) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!trapezium_median(base1, base2, &median)) {
        if (fputs("Unable to calculate the median.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Median: %.10g\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}