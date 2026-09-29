#include <stdio.h>

int count_equal_numbers(int a, int b, int c) {
    if (a == b && b == c) {
        return 3;
    }
    if (a == b || b == c || a == c) {
        return 2;
    }
    return 0;
}

int main() {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    int result = count_equal_numbers(a, b, c);
    printf("%d\n", result);
    return 0;
}