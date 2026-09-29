#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_positive_integer(const char *str) {
    if (str == NULL || str[0] == '\0') return false;
    while (*str) {
        if (*str < '0' || *str > '9') return false;
        str++;
    }
    return true;
}

int sum_of_squares(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int odd_number = 2 * i - 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2146453540 + 5499025 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:2051,execs:647,op:havoc,rep:5)
         */
        sum += odd_number * odd_number;
    }
    return sum;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[12];
    int n;

    printf("Enter the value of n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (!is_valid_positive_integer(input)) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    long l_n = strtol(input, NULL, 10);
    if (l_n < 1 || l_n > INT_MAX || l_n != (int)l_n) {
        printf("Please enter a positive integer within the valid range.\n");
        return 1;
    }

    n = (int)l_n;

    int result = sum_of_squares(n);
    printf("The sum of squares of the first %d odd natural numbers is: %d\n", n, result);

    return 0;
}