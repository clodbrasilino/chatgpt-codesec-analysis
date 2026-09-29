#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 256

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

static int read_line(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    ch = fgetc(stdin);
    if (ch == EOF) {
        return ferror(stdin) ? 0 : 1;
    }

    while (ch != '\n' && ch != EOF) {
        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
        return 0;
    }

    return 0;
}

static int read_positive_double(const char *prompt, double *value)
{
    char buffer[INPUT_BUFFER_SIZE];
    char *end;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(buffer, sizeof buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed <= 0.0) {
        return 0;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\r' ||
           *end == '\f' ||
           *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    double base1;
    double base2;
    double median;

    if (!read_positive_double("Enter the first base: ", &base1) ||
        !read_positive_double("Enter the second base: ", &base2)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!trapezium_median(base1, base2, &median)) {
        fputs("Unable to calculate the median.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Median: %.10g\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}