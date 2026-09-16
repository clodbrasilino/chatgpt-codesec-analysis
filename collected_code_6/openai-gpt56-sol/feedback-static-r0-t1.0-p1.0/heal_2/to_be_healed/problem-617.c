#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int jumps_required(double distance, double jump_length,
                          unsigned long long *result)
{
    double ratio;

    if (result == NULL || !isfinite(distance) || !isfinite(jump_length) ||
        distance < 0.0 || jump_length <= 0.0) {
        return 0;
    }

    if (distance == 0.0) {
        *result = 0;
        return 1;
    }

    ratio = distance / jump_length;

    if (!isfinite(ratio) || ratio > (double)ULLONG_MAX) {
        return 0;
    }

    if (ratio <= 1.0) {
        *result = distance == jump_length ? 1ULL : 2ULL;
    } else {
        *result = (unsigned long long)ceil(ratio);
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end;
    double distance;
    double jump_length;
    unsigned long long result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <distance> <jump_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    distance = strtod(argv[1], &end);
    if (errno != 0 || end == argv[1] || *end != '\0') {
        fprintf(stderr, "Invalid distance\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    jump_length = strtod(argv[2], &end);
    if (errno != 0 || end == argv[2] || *end != '\0') {
        fprintf(stderr, "Invalid jump length\n");
        return EXIT_FAILURE;
    }

    if (!jumps_required(distance, jump_length, &result)) {
        fprintf(stderr, "Unable to calculate the number of jumps\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);
    return EXIT_SUCCESS;
}