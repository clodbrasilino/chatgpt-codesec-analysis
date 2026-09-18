#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_digits(long num) {
    int count = 0;
    if (num == 0) return 1;
    if (num < 0) {
        if (num == LONG_MIN) {
            num = (unsigned long)(-num);
        } else {
            num = -num;
        }
    }
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    int digits = count_digits(number);
    printf("Number of digits: %d\n", digits);
    return 0;
}