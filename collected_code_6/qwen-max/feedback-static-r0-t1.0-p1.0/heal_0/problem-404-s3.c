#include <stdio.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int x = 10, y = 20;
    int result = min(x, y);
    printf("The minimum of %d and %d is %d\n", x, y, result);
    return 0;
}