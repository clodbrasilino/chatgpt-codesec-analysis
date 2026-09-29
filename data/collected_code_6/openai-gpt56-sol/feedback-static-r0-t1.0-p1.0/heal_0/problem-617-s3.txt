#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int jumps_required(double distance, double jump_length, unsigned long long *result)
{
    double ratio;
    double jumps;

    if (result == NULL || !isfinite(distance) || !isfinite(jump_length) ||
        distance < 0.0 || jump_length <= 0.0) {
        return -1;
    }

    if (distance == 0.0) {
        *result = 0;
        return 0;
    }

    ratio = distance / jump_length;

    if (!isfinite(ratio)) {
        return -1;
    }

    if (ratio == 1.0) {
        *result = 1;
        return 0;
    }

    jumps = ratio < 2.0 ? 2.0 : ceil(ratio);

    if (jumps > (double)ULLONG_MAX) {
        return -1;
    }

    *result = (unsigned long long)jumps;
    return 0;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' || !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(int argc, char *argv[])
{
    double distance;
    double jump_length;
    unsigned long long jumps;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <distance> <jump_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_double(argv[1], &distance) != 0 ||
        parse_double(argv[2], &jump_length) != 0) {
        fprintf(stderr, "Invalid numeric input\n");
        return EXIT_FAILURE;
    }

    if (jumps_required(distance, jump_length, &jumps) != 0) {
        fprintf(stderr, "Distance must be nonnegative and jump length must be positive\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", jumps);
    return EXIT_SUCCESS;
}