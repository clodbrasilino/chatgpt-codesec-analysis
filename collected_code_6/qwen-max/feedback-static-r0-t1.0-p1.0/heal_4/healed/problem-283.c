#include <stdio.h>
#include <stdlib.h>

int digit_frequency_check(int num) {
    int freq[10] = {0};
    while (num > 0) {
        int digit = num % 10;
        freq[digit]++;
        if (freq[digit] > digit) {
            return 0;
        }
        num /= 10;
    }
    return 1;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    if (digit_frequency_check(n)) {
        printf("The frequency of each digit is less than or equal to the digit itself.\n");
    } else {
        printf("The frequency of some digits is greater than the digit itself.\n");
    }

    return 0;
}