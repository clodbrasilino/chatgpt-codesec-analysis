#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int maximum_cuboid_volume(double side_sum, double *volume)
{
    double side;
    double limit;

    if (volume == NULL || !isfinite(side_sum) || side_sum < 0.0) {
        return -1;
    }

    side = side_sum / 3.0;
    limit = cbrt(DBL_MAX);

    if (side > limit) {
        return -1;
    }

    *volume = side * side * side;

    return isfinite(*volume) ? 0 : -1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double side_sum;
    double volume;
    int status = EXIT_FAILURE;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        goto cleanup;
    }

    if (length == 0 || input[length - 1] != '\n') {
        int ch = fgetc(stdin);

        if (ch != EOF) {
            goto cleanup;
        }

        if (ferror(stdin)) {
            goto cleanup;
        }
    }

    errno = 0;
    side_sum = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    if (maximum_cuboid_volume(side_sum, &volume) != 0) {
        goto cleanup;
    }

    if (printf("%.10g\n", volume) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}