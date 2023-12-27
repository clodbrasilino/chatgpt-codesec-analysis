#include <stdio.h>

int factorial(int num) {
    int fact = 1;
    for (int i = 1; i <= num; i++) {
        fact = fact * i;
    }
    return fact;
}

int findEntringerNumber(int n, int k) {
    int numerator = factorial(n + k - 1);
    int denominator = factorial(n) * factorial(k - 1);
    return numerator / denominator;
}

int main() {
    int n = 0, k = 0;

    printf("Enter the values of n and k: ");
    scanf("%d %d", &n, &k);

    printf("Entringer number e(%d, %d) = %d\n", n, k, findEntringerNumber(n, k));
    return 0;
}