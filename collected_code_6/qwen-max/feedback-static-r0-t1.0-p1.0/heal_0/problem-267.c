#include <stdio.h>

int sum_of_squares(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int odd_number = 2 * i - 1;
        sum += odd_number * odd_number;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }
    if (n < 1) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    int result = sum_of_squares(n);
    printf("The sum of squares of the first %d odd natural numbers is: %d\n", n, result);
    return 0;
}