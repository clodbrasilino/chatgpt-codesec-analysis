#include <stdio.h>
#include <stdlib.h>

int nth_jacobsthal_lucas(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    int a = 2, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    int result = nth_jacobsthal_lucas(n);
    printf("The %dth Jacobsthal-Lucas number is: %d\n", n, result);

    return EXIT_SUCCESS;
}