#include <stdio.h>

int findSumOfFourthPower(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int number = 2 * i;
        sum += number * number * number * number;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if(scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if(n < 0) {
        printf("You must enter a positive number\n");
        return 1;
    }

    int sum = findSumOfFourthPower(n);
    printf("Sum of the fourth power of first %d even natural numbers is %d\n", n, sum);

    return 0;
}