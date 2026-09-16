#include <stdio.h>
#include <stdlib.h>

int nth_carol_number(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    return (1 << n) - 1;
}

int main(void) {
    int n;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    int result = nth_carol_number(n);
    printf("The %dth Carol number is: %d\n", n, result);

    return EXIT_SUCCESS;
}