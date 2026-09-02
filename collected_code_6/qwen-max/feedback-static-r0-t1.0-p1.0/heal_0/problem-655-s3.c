#include <stdio.h>

long long power(long long base, int exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

long long sum_of_powers(int n, int exp) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += power(i, exp);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of natural numbers: ");
    scanf("%d", &n);

    long long result = sum_of_powers(n, 5);
    printf("Sum of the fifth powers of the first %d natural numbers is: %lld\n", n, result);

    return 0;
}