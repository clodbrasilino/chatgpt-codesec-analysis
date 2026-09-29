#include <stdio.h>

double geometricSum(int n) {
    double sum = 1.0;

    for (int i = 1; i <= n-1; i++) {
        sum += 1.0 / i;
    }

    return sum;
}

int main() {
    int n;
    printf("Enter a value for n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);

    double result = geometricSum(n);
    printf("Geometric sum of n-1: %.2f\n", result);

    return 0;
}