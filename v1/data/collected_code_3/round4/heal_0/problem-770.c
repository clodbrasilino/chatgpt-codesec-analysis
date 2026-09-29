#include <stdio.h>

long long int sumOfFourthPower(int n) {
    long long int sum = 0;
    int i, odd = 1;

    for(i = 1; i <= n; i++) {
        sum += odd * odd * odd * odd;
        odd += 2;
    }

    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    printf("Sum of fourth powers of first %d odd numbers is: %lld\n", n, sumOfFourthPower(n));

    return 0;
}