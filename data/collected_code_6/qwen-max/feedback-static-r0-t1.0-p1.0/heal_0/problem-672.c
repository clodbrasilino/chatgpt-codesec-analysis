#include <stdio.h>

int max_of_three(int a, int b, int c) {
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

int main() {
    int x = 10, y = 20, z = 30;
    int result = max_of_three(x, y, z);
    printf("The maximum of %d, %d, and %d is: %d\n", x, y, z, result);
    return 0;
}