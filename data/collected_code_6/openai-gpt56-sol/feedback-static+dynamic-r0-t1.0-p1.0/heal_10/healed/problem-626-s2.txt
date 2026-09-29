#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int largest_inscribed_triangle(double radius, double *area)
{
    if (area == NULL || !isfinite(radius) || radius <= 0.0 ||
        radius > sqrt(DBL_MAX)) {
        return -1;
    }

    *area = radius * radius;
    return 0;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double area;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || largest_inscribed_triangle(radius, &area) != 0) {
        fprintf(stderr, "Radius must be a positive finite number.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        fprintf(stderr, "Failed to write the result.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}