#include <stdio.h>

int max_of_three(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

int main() {
    int x = 10, y = 20, z = 30;
    int result = max_of_three(x, y, z);
    printf("Maximum of %d, %d, and %d is %d\n", x, y, z, result);
    return 0;
}