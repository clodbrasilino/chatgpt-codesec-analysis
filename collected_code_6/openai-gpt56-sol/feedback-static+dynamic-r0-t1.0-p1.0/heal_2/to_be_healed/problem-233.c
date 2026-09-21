#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double radius, double height, double *area)
{
    double result;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return 0;
    }

    result = 2.0 * acos(-1.0) * radius * height;
    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

static int read_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end;
    double result;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (buffer[0] == '\0') {
        return 0;
    }

    {
        size_t length = 0;

        while (length < sizeof buffer && buffer[length] != '\0') {
            ++length;
        }

        if (length == sizeof buffer) {
            return 0;
        }

        if (length > 0 && buffer[length - 1] != '\n' && !feof(stdin)) {
            discard_line();
            return 0;
        }
    }

    errno = 0;
    end = NULL;
    result = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(result)) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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