#include <stdio.h>
#include <stdlib.h>

double geometric_sum(int n, double r) {
    if (n < 1) {
        return 0.0;
    }
    if (r == 1.0) {
        return (double)(n - 1);
    }
    return (1.0 - pow(r, (double)(n - 1))) / (1.0 - r);
}

int main(int argc, char *argv[]) {
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