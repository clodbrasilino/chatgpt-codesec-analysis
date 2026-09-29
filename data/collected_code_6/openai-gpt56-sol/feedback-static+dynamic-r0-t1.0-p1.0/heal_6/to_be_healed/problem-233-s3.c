#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int lateral_surface_area(double radius, double height, double *area)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (area == NULL ||
        !isfinite(radius) ||
        !isfinite(height) ||
        radius < 0.0 ||
        height < 0.0) {
        return 0;
    }

    if (radius != 0.0 && height > (DBL_MAX / (2.0 * pi)) / radius) {
        return 0;
    }

    result = 2.0 * pi * radius * height;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[4096];
    char *end;
    double parsed;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(line, '\n') == NULL) {
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return 0;
        }

        return 0;
    }

    errno = 0;
    parsed = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed < 0.0) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    double radius;
    double height;
    double area;

    if (!read_nonnegative_double("Enter the radius: ", &radius) ||
        !read_nonnegative_double("Enter the height: ", &height)) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!lateral_surface_area(radius, height, &area)) {
        if (fputs("Unable to calculate the lateral surface area.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}