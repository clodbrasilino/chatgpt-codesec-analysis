#include <stdio.h>
#include <stdlib.h>

long long jacobsthal_lucas(long n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    long long a = 2, b = 1, c;
    for (long i = 2; i <= n; i++) {
        c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    long long result = jacobsthal_lucas(n);
    printf("The %ldth Jacobsthal-Lucas number is: %lld\n", n, result);
    return EXIT_SUCCESS;
}