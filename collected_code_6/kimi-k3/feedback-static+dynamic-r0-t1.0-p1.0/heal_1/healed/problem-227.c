#include <stdio.h>

int min_of_three(int a, int b, int c);

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    printf("%d\n", min_of_three(a, b, c));
    return 0;
}

int min_of_three(int a, int b, int c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}