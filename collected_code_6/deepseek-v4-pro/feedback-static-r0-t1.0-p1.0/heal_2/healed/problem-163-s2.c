#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

double regular_polygon_area(unsigned int n, double side_length)
{
    if (n < 3 || side_length <= 0.0) {
        errno = EINVAL;
        return -1.0;
    }

    double tan_value = tan(M_PI / n);
    if (tan_value == 0.0) {
        errno = ERANGE;
        return -1.0;
    }

    if (side_length > sqrt((DBL_MAX * 4.0 * tan_value) / n)) {
        errno = ERANGE;
        return -1.0;
    }

    double area = (n * side_length * side_length) / (4.0 * tan_value);
    return area;
}

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <sides> <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long sides = strtoul(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || sides > UINT_MAX) {
        fprintf(stderr, "Invalid number of sides\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    double side_len = strtod(argv[2], &endptr);
    if (errno != 0 || *endptr != '\0') {
        fprintf(stderr, "Invalid side length\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    double area = regular_polygon_area((unsigned int)sides, side_len);
    if (errno != 0) {
        perror("Error calculating polygon area");
        return EXIT_FAILURE;
    }

    printf("%.15f\n", area);
    return EXIT_SUCCESS;
}