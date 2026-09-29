#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long nthCarol(int n) {
    if (n < 1)
        return -1;

    long long res = pow(2, n) - 1;
    res *= res - 2;
    return res;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid usage. Please provide a single integer argument.\n");
        return EXIT_FAILURE;
    }
    
    int n = atoi(argv[1]);
    if (n < 1) {
        printf("Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }

    long long carol = nthCarol(n);
    if (carol < 1) {
        printf("The number provided is too large. Please use a smaller number.\n");
        return EXIT_FAILURE;
    }

    printf("The %d-th Carol number is %lld.\n", n, carol);
    return EXIT_SUCCESS;
}