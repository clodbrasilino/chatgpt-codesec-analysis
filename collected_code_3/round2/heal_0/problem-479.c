#include <stdio.h>

int firstDigit(int n) {
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("First digit: %d\n", firstDigit(number));
    return 0;
}