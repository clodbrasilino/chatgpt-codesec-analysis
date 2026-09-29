#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_not_multiple(unsigned long long n, unsigned long long m) {
    if (m <= 1) {
        return 0;
    }
    return n + (n - 1) / (m - 1);
}

int main(void) {
    unsigned long long n;
    unsigned long long m;
    unsigned long long result;

    printf("Enter n: ");
    if (scanf("%llu", &n) != 1) {
        return EXIT_FAILURE;
    }

    printf("Enter m: ");
    if (scanf("%llu", &m) != 1) {
        return EXIT_FAILURE;
    }

    if (m <= 1) {
        printf("m must be greater than 1.\n");
        return EXIT_FAILURE;
    }
    
    if (n == 0) {
        printf("n must be greater than 0.\n");
        return EXIT_FAILURE;
    }

    result = find_nth_not_multiple(n, m);
    printf("The %llu-th number not a multiple of %llu is: %llu\n", n, m, result);

    return EXIT_SUCCESS;
}