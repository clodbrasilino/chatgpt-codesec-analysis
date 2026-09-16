#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int triangle_is_possible(double angle1, double angle2, double angle3)
{
    const double sum = angle1 + angle2 + angle3;
    const double tolerance = 1e-9;

    return isfinite(angle1) &&
           isfinite(angle2) &&
           isfinite(angle3) &&
           angle1 > 0.0 &&
           angle2 > 0.0 &&
           angle3 > 0.0 &&
           fabs(sum - 180.0) <= tolerance;
}

static int parse_angle(const char *text, double *angle)
{
    char *end = NULL;

    errno = 0;
    *angle = strtod(text, &end);

    return errno == 0 &&
           end != text &&
           *end == '\0' &&
           isfinite(*angle);
}

int main(int argc, char * const argv[])
{
    double angle1;
    double angle2;
    double angle3;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <angle1> <angle2> <angle3>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_angle(argv[1], &angle1) ||
        !parse_angle(argv[2], &angle2) ||
        !parse_angle(argv[3], &angle3)) {
        fprintf(stderr, "Invalid angle input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n",
           triangle_is_possible(angle1, angle2, angle3)
               ? "Triangle is possible"
               : "Triangle is not possible");

    return EXIT_SUCCESS;
}