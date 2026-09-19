#include <stdio.h>
#include <stdint.h>

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
    if (scanf("%ld", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int result = count_digits(number);
    if (result == 0) {
        printf("No digits found.\n");
    } else {
        printf("Number of digits: %d\n", result);
    }
    return 0;
}