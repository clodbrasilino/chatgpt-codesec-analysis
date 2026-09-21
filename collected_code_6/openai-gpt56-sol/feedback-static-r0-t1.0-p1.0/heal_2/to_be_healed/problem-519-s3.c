#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int tetrahedron_volume(double base_area, double height, double *volume)
{
    double result;

    if (volume == NULL || !isfinite(base_area) || !isfinite(height) ||
        base_area < 0.0 || height < 0.0) {
        return -1;
    }

    /* Possible weaknesses found:
     *  'DBL_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'DBL_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (height != 0.0 && base_area > (3.0 * DBL_MAX) / height) {
        return -1;
    }

    result = (base_area / 3.0) * height;

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

    return ferror(stdin) ? -1 : 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end;
    double parsed_value;
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

    if (buffer[length] != '\n' && !feof(stdin)) {
        if (discard_line() != 0) {
            return -1;
        }
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed_value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed_value) ||
        parsed_value < 0.0) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed_value;
    return 0;
}

int main(void)
{
    double base_area;
    double height;
    double volume;

    if (read_nonnegative_double("Enter the base area: ", &base_area) != 0) {
        fputs("Invalid base area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the perpendicular height: ", &height) != 0) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    if (tetrahedron_volume(base_area, height, &volume) != 0) {
        fputs("Unable to calculate a finite volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}