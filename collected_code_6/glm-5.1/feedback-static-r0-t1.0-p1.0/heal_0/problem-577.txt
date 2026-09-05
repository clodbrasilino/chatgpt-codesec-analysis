#include <stdio.h>

int last_factorial_digit(int n) {
    if (n < 0) {
        return -1;
    }
    if (n >= 5) {
        return 0;
    }
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result % 10;
}

int main() {
    int val;
    if (scanf("%d", &val) == 1) {
        int res = last_factorial_digit(val);
        if (res != -1) {
            printf("%d\n", res);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}