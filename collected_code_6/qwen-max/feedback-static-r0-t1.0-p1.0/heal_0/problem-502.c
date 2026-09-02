#include <stdio.h>

int find_remainder(int a, int b) {
    return a % b;
}

int main() {
    int x = 20;
    int y = 3;
    int result = find_remainder(x, y);
    printf("%d\n", result);
    return 0;
}