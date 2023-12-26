#include <stdio.h>

int nthNonagonalNumber(int n) {
    return (5 * n * n - 3 * n) / 2;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    int result = nthNonagonalNumber(n);
    printf("The nth nonagonal number is: %d\n", result);
    return 0;
}