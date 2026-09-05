#include <stdio.h>

int is_equilateral(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    return (a == b) && (b == c);
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    if (is_equilateral(a, b, c)) {
        printf("Equilateral\n");
    } else {
        printf("Not Equilateral\n");
    }
    return 0;
}