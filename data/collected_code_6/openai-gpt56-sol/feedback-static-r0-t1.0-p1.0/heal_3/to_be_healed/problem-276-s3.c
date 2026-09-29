#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cylinder_volume(double radius, double height, double *volume)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (volume == NULL ||
        !isfinite(radius) ||
        !isfinite(height) ||
        radius < 0.0 ||
        height < 0.0) {
        return -1;
    }

    result = pi * radius * radius * height;

    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n' ? 0 : -1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    double result;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        (void)discard_line();
        return -1;
    }

    errno = 0;
    result = strtod(input, &end);

    if (end == input ||
        errno == ERANGE ||
        !isfinite(result) ||
        result < 0.0) {
        return -1;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\n' ||
           *end == '\r' ||
           *end == '\f' ||
           *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = result;
    return 0;
}

int main(void)
{
    double radius;
    double height;
    double volume;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0) {
        if (fputs("Invalid radius.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the height: ", &height) != 0) {
        if (fputs("Invalid height.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (cylinder_volume(radius, height, &volume) != 0) {
        if (fputs("Unable to calculate the volume.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}