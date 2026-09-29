#include <stdio.h>

long long sumOfPowers(int n) {
    long long sum = 0;
    for(int i = 1; i <= n; i++) {
        long long evenNum = 2 * i;
        long long power = evenNum * evenNum * evenNum * evenNum;
        sum += power;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    long long result = sumOfPowers(n);
    printf("Sum of fourth powers of first %d even natural numbers is %lld\n", n, result);
    return 0;
}