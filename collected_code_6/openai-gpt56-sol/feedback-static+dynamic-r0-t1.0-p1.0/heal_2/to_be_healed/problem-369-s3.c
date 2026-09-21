#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double length, double width, double height,
                                double *area)
{
    double perimeter;

    if (area == NULL ||
        !isfinite(length) || !isfinite(width) || !isfinite(height) ||
        length < 0.0 || width < 0.0 || height < 0.0) {
        return 0;
    }

    perimeter = length + width;
    if (!isfinite(perimeter)) {
        return 0;
    }

    *area = 2.0 * height * perimeter;
    return isfinite(*area);
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

static int read_dimension(const char *name, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    double parsed;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (name == NULL || value == NULL) {
        return 0;
    }

    printf("Enter %s: ", name);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    for (end = input; *end != '\0' && *end != '\n'; ++end) {
    }

    if (*end != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            discard_remaining_input();
            return 0;
        }
    }

    errno = 0;
    end = NULL;
    parsed = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
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

    printf("Lateral surface area: %.2f\n", area);
    return EXIT_SUCCESS;
}