#include <stdio.h>
#include <stdlib.h>

int find_first_digit(int number) {
    if (number == 0) {
        return 0;
    }
    if (number == INT_MIN) {
        return 2;
    }
    int n = abs(number);
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int main(void) {
    int num;
    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }
    int result = find_first_digit(num);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}