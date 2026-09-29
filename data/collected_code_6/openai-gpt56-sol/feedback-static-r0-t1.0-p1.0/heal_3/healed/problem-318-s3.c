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
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double sum;
    double volume;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    sum = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(sum) || sum <= 0.0) {
        free(input);
        fputs("Invalid sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Unexpected characters in input.\n", stderr);
        return EXIT_FAILURE;
    }

    volume = maximum_cuboid_volume(sum);
    free(input);

    if (!isfinite(volume)) {
        fputs("Volume is outside the representable range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}