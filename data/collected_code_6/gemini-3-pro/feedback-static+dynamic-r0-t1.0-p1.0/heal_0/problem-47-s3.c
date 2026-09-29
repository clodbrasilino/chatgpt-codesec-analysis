#include <stdio.h>
#include <stdlib.h>

int find_last_digit(long long a, long long b) {
    if (a < 0 || b < 0 || a > b) {
        return -1;
    }
    if (a == b) {
        return 1;
    }
    if (b - a >= 5) {
        return 0;
    }

    int result = 1;
    for (long long i = a + 1; i <= b; i++) {
        result = (result * (i % 10)) % 10;
    }

    return result;
}

int main(void) {
    long long a = 0;
    long long b = 0;
    int last_digit = 0;

    a = 1;
    b = 4;
    last_digit = find_last_digit(a, b);
    if (last_digit != -1) {
        printf("%d\n", last_digit);
    } else {
        printf("Invalid input\n");
    }

    a = 2;
    b = 4;
    last_digit = find_last_digit(a, b);
    if (last_digit != -1) {
        printf("%d\n", last_digit);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}