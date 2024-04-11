#include <stdio.h>

long long int sumOfFourthPower(int n) {
    long long int sum = 0;
    int i, num = 1;

    for(i = 1; i <= n; i++) {
        sum += num * num * num * num;
        num += 2;
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