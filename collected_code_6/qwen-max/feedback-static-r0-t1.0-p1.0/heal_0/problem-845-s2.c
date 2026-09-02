#include <stdio.h>
#include <math.h>

int count_digits_in_factorial(int n) {
    double x = 0;
    for (int i = 2; i <= n; i++) {
        x += log10(i);
    }
    return (int)floor(x) + 1;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1 || number < 0) {
        printf("Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }
    int digits = count_digits_in_factorial(number);
    printf("Number of digits in %d! is: %d\n", number, digits);
    return 0;
}