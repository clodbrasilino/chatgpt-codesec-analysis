#include <stdio.h>

int find_max(int a, int b, int c) {
    int max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) == 3) {
        printf("%d\n", find_max(a, b, c));
        return 0;
    }
    return 1;
}