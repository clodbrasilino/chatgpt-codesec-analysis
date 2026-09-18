#include <stdio.h>

long long jacobsthal(int n) {
    if (n < 0) {
        printf("Invalid input, please input a non-negative integer.\n");
        return -1;
    }

    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    long long a = 0, b = 1, c;
    
    for (int i = 2; i <= n; i++) {
        c = 2 * a + b;
        a = b;
        b = c;
    }
    
    /* Possible weaknesses found:
     *  use of uninitialized value 'c' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return c;
}

int main() {
    int n;
    printf("Enter the nth Jacobsthal number to find: ");
    if (scanf("%d", &n) != 1) {
        printf("Failed to read the integer.\n");
        return 1;
    }
    
    long long result = jacobsthal(n);
    
    if (result != -1) {
        printf("The Jacobsthal number at position %d is %lld.\n", n, result);
    } else {
        return 1;
    }
    
    return 0;
}