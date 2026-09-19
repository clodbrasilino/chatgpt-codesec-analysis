#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int findFirstDigit(long num) {
    if (num == 0) return 0;
    if (num < 0) num = labs(num);
    if (num == LONG_MAX) return 1;
    int digits = (int)(log10((double)num) + 0.5);
    if (digits < 0 || digits > INT_MAX) return 0;
    return (int)(num / pow(10, digits));
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int firstDigit = findFirstDigit(number);
    if (firstDigit >= 0) {
        printf("The first digit is %d\n", firstDigit);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}