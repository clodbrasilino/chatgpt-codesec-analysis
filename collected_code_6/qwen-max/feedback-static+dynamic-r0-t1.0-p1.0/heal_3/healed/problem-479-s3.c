#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

int findFirstDigit(long num) {
    if (num < 0) num = labs(num);
    if (num == 0) return 0;
    if (num == LONG_MAX) return 9;

    int digits = (int)log10l((long double)num);
    return (int)(num / powl(10.0L, digits));
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    printf("The first digit is %d\n", firstDigit);
    return 0;
}