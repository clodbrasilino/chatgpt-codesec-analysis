#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 256

static int cone_surface_area(double radius, double height, double *area)
{
    double pi;
    double slant_height;
    double result;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    pi = acos(-1.0);
    slant_height = hypot(radius, height);

    if (!isfinite(slant_height)) {
        return -1;
    }

    result = pi * radius * (radius + slant_height);

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];
    char *start;
    char *end;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    if (buffer[0] == '\0') {
        return -1;
    }

    {
        size_t length = 0;

        while (length < sizeof buffer && buffer[length] != '\0') {
            ++length;
        }

        if (length == sizeof buffer) {
            return -1;
        }

        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        } else if (!feof(stdin)) {
            if (discard_line() != 0) {
                return -1;
            }
            return -1;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtod(start, &end);

    if (end == start || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
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
    double area;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0 ||
        read_nonnegative_double("Enter the height: ", &height) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cone_surface_area(radius, height, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}