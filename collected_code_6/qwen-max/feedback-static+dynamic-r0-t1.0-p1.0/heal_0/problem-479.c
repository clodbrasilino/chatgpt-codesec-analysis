#include <stdio.h>
#include <math.h>

int findFirstDigit(long n) {
    if (n < 0) n = -n;
    return (int)(n / pow(10, (int)log10(n)));
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    if (scanf("%ld", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int firstDigit = findFirstDigit(number);
    printf("The first digit of %ld is %d.\n", number, firstDigit);
    return 0;
}