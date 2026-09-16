#include <stdio.h>

int find_max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main(void) {
    int x = 10;
    int y = 20;
    int result = find_max(x, y);
    if (printf("%d\n", result) < 0) {
        return 1;
    }
    return 0;
}