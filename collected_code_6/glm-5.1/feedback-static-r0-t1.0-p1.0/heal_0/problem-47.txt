#include <stdio.h>

int last_digit_factorial_division(int a, int b) {
    if (a < 0 || b < 0) {
        return -1;
    }
    if (a > b) {
        return 0;
    }
    long long result = 1;
    for (int i = a + 1; i <= b; i++) {
        result = (result * (i % 10)) % 10;
    }
    return (int)result;
}

int main() {
    int a = 5;
    int b = 10;
    int result = last_digit_factorial_division(a, b);
    printf("%d\n", result);
    return 0;
}