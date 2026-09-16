#include <stdio.h>

int last_two_digits_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return 1;
    }
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % 100;
        if (result == 0) {
            return 0;
        }
    }
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int res = last_two_digits_factorial(n);
    if (res == -1) {
        return 1;
    }
    printf("%02d\n", res);
    return 0;
}