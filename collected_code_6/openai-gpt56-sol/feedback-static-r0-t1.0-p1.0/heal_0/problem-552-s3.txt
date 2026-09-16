#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int is_linear(const double *sequence, size_t length)
{
    double difference;
    size_t i;

    if (sequence == NULL || length < 3U) {
        return 1;
    }

    difference = sequence[1] - sequence[0];

    for (i = 2U; i < length; ++i) {
        double current_difference = sequence[i] - sequence[i - 1U];
        double scale = fmax(1.0, fmax(fabs(difference), fabs(current_difference)));

        if (fabs(current_difference - difference) > 1e-9 * scale) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    size_t length;
    double *sequence = NULL;
    size_t i;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*sequence)) {
        return EXIT_FAILURE;
    }

    if (length > 0U) {
        sequence = malloc(length * sizeof(*sequence));
        if (sequence == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < length; ++i) {
        if (scanf("%lf", &sequence[i]) != 1 || !isfinite(sequence[i])) {
            free(sequence);
            return EXIT_FAILURE;
        }
    }

    puts(is_linear(sequence, length) ? "Linear" : "Not linear");

    free(sequence);
    return EXIT_SUCCESS;
}