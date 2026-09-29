#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_volume(double side, double *volume)
{
    double result;

    if (volume == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    result = side * side * side;

    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

int main(void)
{
    char input[256];
    char *end;
    double side;
    double volume;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the side length.\n");
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid side length.\n");
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || cube_volume(side, &volume) != 0) {
        fprintf(stderr,
                "Side length must be a finite, nonnegative value whose volume is representable.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", volume) < 0) {
        fprintf(stderr, "Failed to write the volume.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}