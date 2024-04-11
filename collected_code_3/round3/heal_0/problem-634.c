#include <stdio.h>

long long sumOfFourthPower(int n) {
    long long sum = 0;
    int i;
    for(i = 2; i <= 2*n; i += 2) {
        sum += i*i*i*i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of fourth powers of first %d even natural numbers is %lld\n", n, sumOfFourthPower(n));
    return 0;
}