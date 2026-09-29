#include <stdio.h>
#include <stdlib.h>

int diffEvenOddDigits(int num) {
    int diff, sumEvens = 0, sumOdds = 0, digit;

    while (num > 0) {
        digit = num % 10;
        if (digit % 2 == 0)
            sumEvens += digit;
        else
            sumOdds += digit;

        num /= 10;
    }

    diff = abs(sumEvens - sumOdds);

    return diff;
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);
    
    if(num < 0){
        printf("Enter a positive number\n");
        return 1;
    }

    printf("Difference between sum of even and odd digits: %d\n", diffEvenOddDigits(num));

    return 0;
}