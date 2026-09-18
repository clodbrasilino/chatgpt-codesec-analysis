#include <stdio.h>

long long int fourthPowerSum(int n) {
    long long int sum = 0;
    for (int i = 0; i <= n; i++) {
        long long int evenNumber = 2 * i;
        long long int fourthPower = evenNumber * evenNumber * evenNumber * evenNumber;
        sum += fourthPower;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of even natural numbers to sum: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Error: Input must be a positive integer.\n");
        return 1;
    }

    long long int sum = fourthPowerSum(n);
    printf("The sum of the fourth powers of the first %d even natural numbers is: %lld\n", n, sum);

    return 0;
}