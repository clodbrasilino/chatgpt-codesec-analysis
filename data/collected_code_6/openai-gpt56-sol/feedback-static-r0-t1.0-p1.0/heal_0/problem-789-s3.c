#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_perimeter(size_t side_count, double side_length,
                               double *perimeter)
{
    if (perimeter == NULL || side_count < 3U || !isfinite(side_length) ||
        side_length <= 0.0) {
        return -1;
    }

    if (side_length > HUGE_VAL / (double)side_count) {
        return -1;
    }

    *perimeter = (double)side_count * side_length;
    return isfinite(*perimeter) ? 0 : -1;
}

int main(void)
{
    unsigned long long input_side_count;
    char trailing_character;
    double side_length;
    double perimeter;

    errno = 0;
    if (scanf("%llu %lf %c", &input_side_count, &side_length,
              &trailing_character) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || input_side_count > (unsigned long long)SIZE_MAX ||
        calculate_perimeter((size_t)input_side_count, side_length,
                            &perimeter) != 0) {
        fputs("Invalid polygon dimensions\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}