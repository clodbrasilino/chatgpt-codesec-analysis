#include <stdio.h>

int last_digit_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n >= 5) {
        return 0;
    }
    int fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact % 10;
}

int main() {
    int n;
    if (scanf("%d", &n) == 1) {
        int res = last_digit_factorial(n);
        if (res == -1) {
            printf("%d\n", -1);
        } else {
            printf("%d\n", res);
        }
    }
    return 0;
}