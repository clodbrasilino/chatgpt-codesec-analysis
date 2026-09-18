#include <stdio.h>

long long sumOfFourthPower(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i * i * i * i;
    }
    return sum;
}

int main() {
    int n = 0;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input. Please enter a valid integer number.\n");
        return 1;
    }
    if (n < 0) {
        printf("Input should be a non-negative integer\n");
        return 1;
    }
    long long result = sumOfFourthPower(n);
    printf("The sum of fourth powers of first %d natural numbers is: %lld\n", n, result);

    return 0;
}