#include <stdio.h>

long long int sumOfFifthPower(int n) {
    long long int sum = 0;
    for(int i = 1; i <= n; i++) {
        long long int evenNum = 2 * i;
        long long int fifthPower = evenNum * evenNum * evenNum * evenNum * evenNum;
        sum += fifthPower;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of fifth powers of first %d even numbers is: %lld\n", n, sumOfFifthPower(n));
    return 0;
}