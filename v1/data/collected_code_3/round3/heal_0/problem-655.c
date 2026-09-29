#include <stdio.h>

long long int sumOfFifthPowers(int n) {
    long long int sum = 0;
    for(int i = 1; i <= n; i++) {
        long long int power = 1;
        for(int j = 0; j < 5; j++) {
            power *= i;
        }
        sum += power;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of fifth powers of first %d natural numbers is %lld\n", n, sumOfFifthPowers(n));
    return 0;
}