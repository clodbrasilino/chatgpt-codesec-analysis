#include <stdio.h>
#include <stdlib.h>

int nth_jacobsthal_lucas(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    int a = 2, b = 1;
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 1073741825 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:80,execs:50,op:havoc,rep:2)
         */
        int c = 2 * a + b;
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

    if (n < 0) {
        fprintf(stderr, "Input must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    int result = nth_jacobsthal_lucas(n);
    printf("The %dth Jacobsthal-Lucas number is: %d\n", n, result);

    return EXIT_SUCCESS;
}