#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int square_pyramid_surface_area(double base_side, double height,
                                       double *area)
{
    double half_side;
    double slant_height;
    double base_area;
    double lateral_area;

    if (area == NULL || !isfinite(base_side) || !isfinite(height) ||
        base_side < 0.0 || height < 0.0) {
        return -1;
    }

    half_side = base_side / 2.0;
    slant_height = hypot(height, half_side);

    if (!isfinite(slant_height) ||
        (base_side != 0.0 &&
         (base_side > DBL_MAX / base_side ||
          slant_height > DBL_MAX / base_side))) {
        return -1;
    }

    base_area = base_side * base_side;
    lateral_area = base_side * slant_height;

    if (!isfinite(base_area) || !isfinite(lateral_area) ||
        lateral_area > (DBL_MAX - base_area) / 2.0) {
        return -1;
    }

    *area = base_area + 2.0 * lateral_area;
    return isfinite(*area) ? 0 : -1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end;
    double parsed;
    size_t length;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == sizeof buffer) {
        return -1;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char remainder[256];
        int newline_found = 0;

        do {
            if (fgets(remainder, sizeof remainder, stdin) == NULL) {
                if (ferror(stdin)) {
                    return -1;
                }
                break;
            }

            for (size_t i = 0; remainder[i] != '\0'; ++i) {
                if (remainder[i] == '\n') {
                    newline_found = 1;
                    break;
                }
            }
        } while (!newline_found);

        return -1;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed) ||
        parsed < 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
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
    double base_side;
    double height;
    double area;

    if (read_nonnegative_double("Enter the base side length: ",
                                &base_side) != 0) {
        fputs("Invalid base side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the vertical height: ",
                                &height) != 0) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    if (square_pyramid_surface_area(base_side, height, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}