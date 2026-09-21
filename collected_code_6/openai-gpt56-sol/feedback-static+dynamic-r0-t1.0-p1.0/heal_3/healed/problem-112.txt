#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    const double pi = acos(-1.0);
    double value;

    if (result == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    value = 2.0 * (2.0 * pi * radius + height);

    if (!isfinite(value)) {
        return -1;
    }

    *result = value;
    return 0;
}

static int read_double(double *value)
{
    int status;

    if (value == NULL) {
        return -1;
    }

    errno = 0;
    status = scanf("%lf", value);

    if (status != 1 || errno == ERANGE || !isfinite(*value)) {
        return -1;
    }

    return 0;
}

static int input_ended(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF && isspace((unsigned char)ch));

    return ch == '\n' || ch == EOF;
}

int main(void)
{
    double radius;
    double height;
    double perimeter;

    if (read_double(&radius) != 0 ||
        read_double(&height) != 0 ||
        !input_ended()) {
        return EXIT_FAILURE;
    }

    if (cylinder_perimeter(radius, height, &perimeter) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.6f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}