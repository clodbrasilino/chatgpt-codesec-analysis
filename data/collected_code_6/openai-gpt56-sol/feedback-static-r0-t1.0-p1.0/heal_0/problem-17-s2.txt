#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int square_perimeter(double side, double *perimeter)
{
    if (perimeter == NULL || side < 0.0) {
        return -1;
    }

    *perimeter = 4.0 * side;
    return 0;
}

int main(void)
{
    char input[256];
    char *end = NULL;
    double side = 0.0;
    double perimeter = 0.0;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (errno == ERANGE || end == input || (*end != '\n' && *end != '\0')) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (square_perimeter(side, &perimeter) != 0) {
        fputs("Side length must be nonnegative.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}