#include <stdio.h>

int last_digit_factorial_div(int a, int b) {
    int last_digit_a = 1, last_digit_b = 1;
    for (int i = 2; i <= a; ++i) {
        last_digit_a = (last_digit_a * (i % 10)) % 10;
        if (i <= b) {
            last_digit_b = (last_digit_b * (i % 10)) % 10;
        }
    }
    for (int i = a + 1; i <= b; ++i) {
        last_digit_b = (last_digit_b * (i % 10)) % 10;
    }
    int result = (last_digit_b * 1) % 10; // Last digit of b!
    for (int i = 1; i <= 9; ++i) {
        if ((result * i) % 10 == 1) { // Find the multiplicative inverse of last_digit_a
            result = (result * i) % 10;
            break;
        }
    }
    return result;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", last_digit_factorial_div(a, b));
    return 0;
}