#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

double find_trapezium_median(double a, double b) {
    return (a + b) / 2.0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const argc]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base1> <base2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    errno = 0;
    double a = strtod(argv[1], &endptr1);
    double b = strtod(argv[2], &endptr2);

    if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || !isfinite(a) ||
        endptr2 == argv[2] || *endptr2 != '\0' || !isfinite(b)) {
        fprintf(stderr, "Invalid input: arguments must be valid numbers\n");
        return EXIT_FAILURE;
    }

    double median = find_trapezium_median(a, b);
    printf("%f\n", median);

    return EXIT_SUCCESS;
}