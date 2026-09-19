#include <stdio.h>
#include <stdlib.h>

long long lucas_number(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    long long a = 2, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the position of the Lucas number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    long long result = lucas_number(n);
    printf("The %dth Lucas number is: %lld\n", n, result);

    return EXIT_SUCCESS;
}