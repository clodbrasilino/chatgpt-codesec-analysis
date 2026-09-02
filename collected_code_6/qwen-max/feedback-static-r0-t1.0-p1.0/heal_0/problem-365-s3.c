#include <stdio.h>

int count_digits(long num) {
    int count = 0;
    if (num == 0) return 1;
    if (num < 0) num = -num;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    printf("Number of digits: %d\n", count_digits(number));
    return 0;
}