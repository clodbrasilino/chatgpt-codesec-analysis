#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_lateral_surface_area(double radius, double slant_height,
                                     double *area)
{
    if (area == NULL || !isfinite(radius) || !isfinite(slant_height) ||
        radius < 0.0 || slant_height < 0.0) {
        return -1;
    }

    *area = acos(-1.0) * radius * slant_height;

    if (!isfinite(*area)) {
        return -1;
    }

    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end = NULL;
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

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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
    double slant_height;
    double area;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0 ||
        read_nonnegative_double("Enter the slant height: ", &slant_height) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cone_lateral_surface_area(radius, slant_height, &area) != 0) {
        fputs("Unable to calculate the area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}