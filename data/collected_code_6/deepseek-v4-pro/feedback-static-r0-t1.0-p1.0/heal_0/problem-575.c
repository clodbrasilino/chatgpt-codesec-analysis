#include <stdio.h>
#include <stdlib.h>

int find_nth_non_multiple(int n, int k) {
    if (n <= 0 || k <= 0) {
        return -1;
    }
    return n + (n - 1) / (k - 1);
}

int main(void) {
    int n, k, result;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter k: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = find_nth_non_multiple(n, k);
    if (result == -1) {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    printf("The %d-th number not divisible by %d is: %d\n", n, k, result);

    return EXIT_SUCCESS;
}