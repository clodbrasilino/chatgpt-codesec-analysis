#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int largest_inscribed_triangle(double radius, double *area)
{
    double result;

    if (area == NULL || !isfinite(radius) || radius <= 0.0) {
        return -1;
    }

    result = radius * radius;
    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double area;
    size_t newline_pos;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    newline_pos = strcspn(input, "\n");

    if (input[newline_pos] == '\n') {
        input[newline_pos] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    if (input[0] == '\0') {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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