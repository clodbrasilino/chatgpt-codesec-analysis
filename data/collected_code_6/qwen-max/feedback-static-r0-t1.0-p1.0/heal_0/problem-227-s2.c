#include <stdio.h>

int min_of_three(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int main() {
    int x = 10, y = 20, z = 5;
    int result = min_of_three(x, y, z);
    printf("Minimum of %d, %d, and %d is: %d\n", x, y, z, result);
    return 0;
}