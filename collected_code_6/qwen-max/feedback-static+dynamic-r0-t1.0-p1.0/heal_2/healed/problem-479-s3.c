#include <stdio.h>
#include <math.h>
#include <limits.h>

int findFirstDigit(long num) {
    if (num == 0) return 0;
    if (num < 0) num = labs(num);
    if (num > 0 && num < LONG_MAX) {
        int digits = (int)(log10(num) + 0.5);
        return (int)(num / pow(10, digits));
    }
    return -1; // Return -1 for invalid input
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    if (firstDigit != -1) {
        printf("The first digit is %d\n", firstDigit);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}