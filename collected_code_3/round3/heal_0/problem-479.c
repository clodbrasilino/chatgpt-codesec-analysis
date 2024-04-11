#include <stdio.h>

int firstDigit(int n) {
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("First digit of the number: %d", firstDigit(num));
    return 0;
}