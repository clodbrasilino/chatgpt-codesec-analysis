#include <stdio.h>
#include <stdlib.h>

int digit_frequency_check(int num) {
    int freq[10] = {0};
    while (num > 0) {
        /* Possible weaknesses found:
         *  Assignment 'digit=num%10', assigned value is less than 10
         */
        int digit = num % 10;
        /* Possible weaknesses found:
         *  Condition 'digit<=9' is always true
         *  Condition 'digit<=9' is always true [knownConditionTrueFalse]
         */
        if (digit >= 1 && digit <= 9) {
            freq[digit]++;
            if (freq[digit] > digit) {
                return 0;
            }
        } else if (digit == 0) {
            if (freq[0]++ > 0) {
                return 0;
            }
        } else {
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