#include <stdio.h>
#include <stdbool.h>

int firstDigit(int number) {
    while(number >= 10) {
        number = number / 10;
    }
    return number;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("First digit: %d\n", firstDigit(number));

    return 0;
}