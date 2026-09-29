#include <stdio.h>
#include <math.h>
#include <limits.h>

int findFirstDigit(long num) {
    if (num < 0) num = -num;
    if (num == 0) return 0;
    if (num == LONG_MAX) return 9;
    int digits = (int)log10(num);
    return (int)(num / pow(10, digits));
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    printf("The first digit is %d\n", firstDigit);
    return 0;
}