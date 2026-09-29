#include <stdio.h>
#include <limits.h>

int isValidTriangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a > INT_MAX - b || b > INT_MAX - c || a > INT_MAX - c) {
        return 0;
    }
    if ((a + b > c) && (b + c > a) && (a + c > b)) {
        return 1;
    }
    return 0;
}

int main(void) {
    int a, b, c;
    int result;

    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }

    result = isValidTriangle(a, b, c);

    printf("%s\n", result ? "True" : "False");

    return 0;
}