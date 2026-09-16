#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_abundant(int number);

bool is_abundant(int number) {
    if (number <= 0) {
        return false;
    }

    int divisor_sum = 0;
    
    for (int i = 1; i <= number / 2; i++) {
        if (number % i == 0) {
            divisor_sum += i;
        }
    }
    
    return divisor_sum > number;
}

int main(void) {
    int input_number = 0;

    if (scanf("%d", &input_number) != 1) {
        return EXIT_FAILURE;
    }

    if (input_number <= 0) {
        return EXIT_FAILURE;
    }

    if (is_abundant(input_number)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}