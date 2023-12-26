#include <stdio.h>

int smallestMultiple(int n) {
    int i, result = 1;

    for (i = 1; i <= n; i++) {
        if (result % i != 0) {
            int j;
            for (j = 2; j <= i; j++) {
                if (i % j == 0 && result % j == 0) {
                    result /= j;
                }
            }
            result *= i;
        }
    }

    return result;
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Invalid input! n should be a positive integer.\n");
        return 0;
    }

    printf("The smallest multiple of the first %d numbers is: %d\n", n, smallestMultiple(n));

    return 0;
}
