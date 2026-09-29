#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    double pi;
    double perimeter;

    if (result == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    pi = acos(-1.0);
    perimeter = 2.0 * (2.0 * pi * radius + height);

    if (!isfinite(perimeter)) {
        return -1;
    }

    *result = perimeter;
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' ? 0 : -1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    double parsed;
    size_t length;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    if (length == sizeof input) {
        return -1;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (discard_line() != 0) {
        return -1;
    } else {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(void)
{
    double radius;
    double height;
    double perimeter;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the height: ", &height) != 0) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cylinder_perimeter(radius, height, &perimeter) != 0) {
        fputs("Unable to calculate the perimeter.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Cylinder perimeter: %.6f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}