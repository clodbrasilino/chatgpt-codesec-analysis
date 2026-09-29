#include <stdio.h>
#include <stdlib.h>

int getLastDigit(int number) {
    return abs(number % 10);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("The last digit is %d\n", getLastDigit(number));
    return 0;
}