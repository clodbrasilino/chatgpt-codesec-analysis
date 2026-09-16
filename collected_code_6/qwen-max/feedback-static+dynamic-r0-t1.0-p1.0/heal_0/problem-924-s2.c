#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int x = 5;
    int y = 10;
    int result = max(x, y);
    printf("The maximum of %d and %d is %d\n", x, y, result);
    return 0;
}