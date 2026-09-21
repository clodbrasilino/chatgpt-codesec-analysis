#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096

static int lateral_surface_area(double radius, double height, double *area)
{
    const double pi = acos(-1.0);
    double result;

    if (area == NULL || !isfinite(pi) ||
        !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return 0;
    }

    result = 2.0 * pi * radius * height;
    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i;

        for (i = 0; buffer[i] != '\0'; ++i) {
            if (buffer[i] == '\n') {
                return 1;
            }
        }
    }

    return 0;
}

static int read_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_CAPACITY];
    char *end;
    double result;
    size_t i;
    int has_newline = 0;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    for (i = 0; buffer[i] != '\0'; ++i) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            has_newline = 1;
            break;
        }
    }

    if (!has_newline && !feof(stdin)) {
        discard_line();
        return 0;
    }

    errno = 0;
    end = NULL;
    result = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(result)) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = result;
    return 1;
}

int main(void)
{
    double radius;
    double height;
    double area;

    if (!read_double("Enter the radius: ", &radius) ||
        !read_double("Enter the height: ", &height)) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!lateral_surface_area(radius, height, &area)) {
        if (fputs("Unable to calculate the lateral surface area.\n",
                  stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}