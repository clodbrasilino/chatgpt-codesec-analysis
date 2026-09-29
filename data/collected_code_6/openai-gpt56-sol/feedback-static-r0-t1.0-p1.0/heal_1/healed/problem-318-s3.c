#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double maximum_cuboid_volume(double sum)
{
    double side = sum / 3.0;
    return side * side * side;
}

int main(void)
{
    char input[256];
    char *end;
    double sum;
    double volume;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    sum = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(sum) || sum <= 0.0) {
        fputs("Invalid sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Unexpected characters in input.\n", stderr);
        return EXIT_FAILURE;
    }

    volume = maximum_cuboid_volume(sum);

    if (!isfinite(volume)) {
        fputs("Volume is outside the representable range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}