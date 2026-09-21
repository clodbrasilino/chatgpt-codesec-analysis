#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double geometric_sum(int n, double r) {
    if (n < 1) {
        return 0.0;
    }
    if (r == 1.0) {
        return (double)n;
    }
    return (1.0 - pow(r, (double)n)) / (1.0 - r);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int n;
    double r;
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[2], "%lf", &r) != 1) {
        return EXIT_FAILURE;
    }
    if (n < 1) {
        return EXIT_FAILURE;
    }
    double result = geometric_sum(n, r);
    printf("%.6f\n", result);
    return EXIT_SUCCESS;
}