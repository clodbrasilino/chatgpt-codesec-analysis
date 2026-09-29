#include <stdio.h>
#include <limits.h>

int is_isosceles(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if ((long long)a + b <= c || (long long)b + c <= a || (long long)a + c <= b) {
        return 0;
    }
    return (a == b || b == c || a == c);
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    if (is_isosceles(a, b, c)) {
        printf("Isosceles\n");
    } else {
        printf("Not isosceles\n");
    }
    return 0;
}