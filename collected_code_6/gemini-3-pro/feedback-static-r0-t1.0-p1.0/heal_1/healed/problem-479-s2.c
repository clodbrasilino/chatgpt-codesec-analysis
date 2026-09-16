#include <stdio.h>
#include <stdlib.h>

int get_first_digit(int number);

int get_first_digit(int number) {
    long long num;

    if (number == 0) {
        return 0;
    }

    num = (long long)number;
    if (num < 0) {
        num = -num;
    }

    while (num >= 10) {
        num /= 10;
    }

    return (int)num;
}

int main(void) {
    int test_numbers[] = {1234, -567, 0, 9, -2147483648};
    size_t count = sizeof(test_numbers) / sizeof(test_numbers[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int first_digit = get_first_digit(test_numbers[i]);
        printf("%d\n", first_digit);
    }

    return EXIT_SUCCESS;
}