#include <stdio.h>

int getLastDigit(int num) {
    return num % 10;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Last digit: %d\n", getLastDigit(num));
    return 0;
}