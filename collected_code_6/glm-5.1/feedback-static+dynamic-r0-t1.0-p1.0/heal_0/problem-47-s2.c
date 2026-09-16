#include <stdio.h>

int last_digit_factorial_division(int a, int b) {
    if (a > b || a < 0 || b < 0) {
        return 0;
    }
    if (a == b) {
        return 1;
    }
    return 0;
}

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        return 1;
    }
    int result = last_digit_factorial_division(a, b);
    printf("%d\n", result);
    return 0;
}