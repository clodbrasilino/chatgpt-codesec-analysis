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
    char *input = NULL;
    char *end;
    size_t capacity = 0;
    ssize_t length;
    double side;
    double volume;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fprintf(stderr, "Failed to read the side length.\n");
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fprintf(stderr, "Invalid side length.\n");
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || cube_volume(side, &volume) != 0) {
        free(input);
        fprintf(stderr,
                "Side length must be a finite, nonnegative value whose volume is representable.\n");
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.17g\n", volume) < 0) {
        fprintf(stderr, "Failed to write the volume.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}