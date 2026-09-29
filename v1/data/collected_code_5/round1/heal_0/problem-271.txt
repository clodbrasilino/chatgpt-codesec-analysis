#include <stdio.h>
#include <math.h>

long long int evenPowerSum(int n) {
    long long int sum = 0;
    for (int i = 1; i <= n; i++) {
        long long int even = 2 * i;
        long long int power = pow(even, 5);
        sum += power;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    if (n >= 0) {
        long long int sum = evenPowerSum(n);
        printf("The sum of the fifth powers of the first %d even natural numbers is: %lld\n", n, sum);
    } else {
        printf("Invalid input. Please enter a non-negative integer.\n");
    }
    return 0;
}
