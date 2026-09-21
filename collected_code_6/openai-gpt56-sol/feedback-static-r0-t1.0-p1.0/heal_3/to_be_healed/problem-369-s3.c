#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int lateral_surface_area(double length, double width, double height,
                                double *area)
{
    double sum;

    if (area == NULL ||
        !isfinite(length) ||
        !isfinite(width) ||
        !isfinite(height) ||
        length < 0.0 ||
        width < 0.0 ||
        height < 0.0) {
        return 0;
    }

    if (length > DBL_MAX - width) {
        return 0;
    }

    sum = length + width;

    if (height > DBL_MAX / 2.0 ||
        (height != 0.0 && sum > DBL_MAX / (2.0 * height))) {
        return 0;
    }

    *area = 2.0 * height * sum;
    return isfinite(*area);
}

static int read_dimension(const char *name, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;

    if (name == NULL || value == NULL) {
        return 0;
    }

    if (printf("Enter %s: ", name) < 0 || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    errno = 0;
    end = NULL;
    *value = strtod(input, &end);

    if (end == input ||
        errno == ERANGE ||
        !isfinite(*value) ||
        *value < 0.0) {
        return 0;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\r' ||
           *end == '\v' ||
           *end == '\f') {
        ++end;
    }

    return *end == '\n' || *end == '\0';
}

int main(void)
{
    double length;
    double width;
    double height;
    double area;

    if (!read_dimension("length", &length) ||
        !read_dimension("width", &width) ||
        !read_dimension("height", &height)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lateral_surface_area(length, width, height, &area)) {
        fputs("Unable to calculate the lateral surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}