#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int digit_count(int n) {
    int count = 0;
    if (n == 0) {
        return 1;
    }
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

int have_same_digit_count(int a, int b) {
    int count_a = digit_count(a);
    int count_b = digit_count(b);
    return count_a == count_b;
}

int main(void) {
    int num1, num2;

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (have_same_digit_count(num1, num2)) {
        printf("Numbers have the same number of digits.\n");
    } else {
        printf("Numbers do not have the same number of digits.\n");
    }

    return EXIT_SUCCESS;
}