#include <stdio.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int x = 10;
    int y = 20;
    printf("Minimum of %d and %d is %d\n", x, y, min(x, y));
    return 0;
}