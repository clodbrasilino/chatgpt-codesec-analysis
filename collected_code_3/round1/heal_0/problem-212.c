#include <stdio.h>

long long int sumOfFourthPower(int n) {
    long long int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += i*i*i*i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of fourth powers of first %d natural numbers is %lld\n", n, sumOfFourthPower(n));
    return 0;
}