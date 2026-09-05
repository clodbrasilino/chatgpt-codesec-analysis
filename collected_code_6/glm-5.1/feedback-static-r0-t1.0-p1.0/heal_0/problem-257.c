#include <stdio.h>

void swap(int *a, int *b) {
    if (a == NULL || b == NULL) {
        return;
    }

    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int x = 5;
    int y = 10;

    swap(&x, &y);

    printf("%d %d\n", x, y);

    return 0;
}