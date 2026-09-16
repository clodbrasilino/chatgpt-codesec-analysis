#include <stdio.h>
#include <stdbool.h>

bool isEquilateral(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return false;
    }
    return (a == b && b == c);
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    if (isEquilateral(a, b, c)) {
        printf("Equilateral\n");
    } else {
        printf("Not Equilateral\n");
    }
    return 0;
}