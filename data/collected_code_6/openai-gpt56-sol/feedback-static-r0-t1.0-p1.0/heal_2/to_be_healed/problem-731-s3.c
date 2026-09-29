#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_lateral_surface_area(double radius, double slant_height,
                                     double *area)
{
    double result;

    if (area == NULL || !isfinite(radius) || !isfinite(slant_height) ||
        radius < 0.0 || slant_height < 0.0) {
        return -1;
    }

    result = acos(-1.0) * radius * slant_height;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static void discard_remaining_input(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
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
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        discard_remaining_input();
        return -1;
    }

    if (length > 0 && buffer[length - 1] != '\n' && !feof(stdin)) {
        discard_remaining_input();
        return -1;
    }

    errno = 0;
    end = NULL;
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