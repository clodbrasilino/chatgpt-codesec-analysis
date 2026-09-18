#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int reverse_number(int num, int *overflow) {
    int rev = 0;
    while (num > 0) {
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && num % 10 > 7)) {
            *overflow = 1;
            return 0;
        }
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    *overflow = 0;
    return rev;
}

int is_one_less_than_twice_reverse(int number) {
    int reversed, overflow, twice_reversed;

    overflow = 0;
    reversed = reverse_number(number, &overflow);
    if (overflow) {
        return 0;
    }

    if (reversed > INT_MAX / 2 || (reversed == INT_MAX / 2 && 1 > 0)) {
        return 0;
    }
    twice_reversed = 2 * reversed;

    if (number == twice_reversed - 1) {
        return 1;
    }
    return 0;
}

int main() {
    int test_number;
    printf("Enter a number: ");
    if (scanf("%d", &test_number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_one_less_than_twice_reverse(test_number)) {
        printf("The number is one less than twice its reverse.\n");
    } else {
        printf("The number is not one less than twice its reverse.\n");
    }

    return EXIT_SUCCESS;
}