#include <stdio.h>
#include <stdlib.h>

int are_roots_reciprocal(double a, double c) {
    if (a == 0.0) {
        return 0;
    }
    return (a == c) ? 1 : 0;
}

int main(void) {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    int result = scanf("%lf %lf %lf", &a, &b, &c);
    
    if (result != 3) {
        return EXIT_FAILURE;
    }

    if (a == 0.0) {
        return EXIT_FAILURE;
    }

    if (are_roots_reciprocal(a, c)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return EXIT_SUCCESS;
}