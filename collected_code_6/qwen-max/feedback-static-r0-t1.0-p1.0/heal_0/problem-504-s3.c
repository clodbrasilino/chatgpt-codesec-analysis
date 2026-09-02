#include <stdio.h>
#include <stdlib.h>

long long cube_sum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i * i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    long long result = cube_sum(n);
    printf("Cube sum of first %d natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}