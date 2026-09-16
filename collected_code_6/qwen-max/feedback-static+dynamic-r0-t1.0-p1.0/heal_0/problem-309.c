#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int x = 5;
    int y = 10;
    int result = max(x, y);
    printf("Max: %d\n", result);
    return 0;
}