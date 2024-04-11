#include <stdio.h>

int getLastDigit(int num) {
    return num % 10;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("Last digit: %d\n", getLastDigit(number));
    return 0;
}