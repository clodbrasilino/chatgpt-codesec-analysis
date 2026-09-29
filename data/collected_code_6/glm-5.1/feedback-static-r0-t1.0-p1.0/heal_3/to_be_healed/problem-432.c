#include <stdio.h>
#include <stdlib.h>

double find_trapezium_median(double a, double b) {
    return (a + b) / 2.0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base1> <base2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    double a = strtod(argv[1], &endptr1);
    double b = strtod(argv[2], &endptr2);

    if (endptr1 == argv[1] || *endptr1 != '\0' || endptr2 == argv[2] || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input: arguments must be valid numbers\n");
        return EXIT_FAILURE;
    }

    double median = find_trapezium_median(a, b);
    printf("%f\n", median);

    return EXIT_SUCCESS;
}