#include <stdio.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main(void) {
    int x = 10;
    int y = 20;
    int result = min(x, y);
    printf("%d\n", result);
    return 0;
}