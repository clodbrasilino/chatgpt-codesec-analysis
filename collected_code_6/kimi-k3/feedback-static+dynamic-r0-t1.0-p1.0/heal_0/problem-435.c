#include <stdio.h>

int find_last_digit(int num) {
    return abs(num % 10);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Last digit: %d\n", find_last_digit(num));
    return 0;
}