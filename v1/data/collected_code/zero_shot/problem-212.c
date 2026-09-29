#include<stdio.h>

int sumOfFourthPower(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i * i * i * i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    int result = sumOfFourthPower(n);
    printf("The sum of fourth power of first %d natural numbers is %d\n", n, result);
    return 0;
}