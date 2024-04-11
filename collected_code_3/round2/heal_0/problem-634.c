#include <stdio.h>

long long int sumOfPowers(int n) {
    long long int sum = 0;
    for(int i = 1; i <= n; i++) {
        long long int evenNum = 2 * i;
        long long int power = evenNum * evenNum * evenNum * evenNum;
        sum += power;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of fourth powers of first %d even numbers is: %lld\n", n, sumOfPowers(n));
    return 0;
}