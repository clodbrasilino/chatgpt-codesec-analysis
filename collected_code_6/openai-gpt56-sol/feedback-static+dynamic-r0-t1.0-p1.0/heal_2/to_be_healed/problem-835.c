#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int find_slope(double x1, double y1, double x2, double y2, double *slope)
{
    if (slope == NULL || !isfinite(x1) || !isfinite(y1) ||
        !isfinite(x2) || !isfinite(y2) || x1 == x2) {
        return -1;
    }

    *slope = (y2 - y1) / (x2 - x1);

    return isfinite(*slope) ? 0 : -1;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    *value = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' || !isfinite(*value)) {
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    double x1;
    double y1;
    double x2;
    double y2;
    double slope;

    if (argc != 5) {
        fprintf(stderr, "Usage: %s x1 y1 x2 y2\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_double(argv[1], &x1) != 0 ||
        parse_double(argv[2], &y1) != 0 ||
        parse_double(argv[3], &x2) != 0 ||
        parse_double(argv[4], &y2) != 0) {
        fputs("Error: all coordinates must be finite numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_slope(x1, y1, x2, y2, &slope) != 0) {
        fputs("Error: the slope is undefined or not finite.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Slope: %.17g\n", slope);
    return EXIT_SUCCESS;
}