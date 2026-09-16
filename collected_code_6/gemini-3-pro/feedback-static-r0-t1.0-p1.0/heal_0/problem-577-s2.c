#include <stdio.h>
#include <stdlib.h>

int find_last_digit_of_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1 || n == 2 || n == 3 || n == 4) {
        int fact = 1;
        for (int i = 2; i <= n; i++) {
            fact *= i;
        }
        return fact % 10;
    }
    return 0;
}

int main(void) {
    int number;
    int result;

    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = find_last_digit_of_factorial(number);

    if (result == -1) {
        fprintf(stderr, "Factorial of a negative number is undefined\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}