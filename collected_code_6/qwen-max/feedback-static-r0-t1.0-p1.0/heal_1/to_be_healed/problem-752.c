#include <stdio.h>
#include <stdlib.h>

long long jacobsthal(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
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
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("The %dth Jacobsthal number is: %lld\n", n, jacobsthal(n));
    return EXIT_SUCCESS;
}