#include <stdio.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    int x = 10;
    int y = 20;
    printf("%d\n", min(x, y));
    return 0;
}