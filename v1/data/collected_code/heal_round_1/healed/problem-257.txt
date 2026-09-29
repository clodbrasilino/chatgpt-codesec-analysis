#include <stdio.h>

void swapNumbers(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    swapNumbers(&x,&y);
    printf("%d %d\n", x, y);
    return 0;
}