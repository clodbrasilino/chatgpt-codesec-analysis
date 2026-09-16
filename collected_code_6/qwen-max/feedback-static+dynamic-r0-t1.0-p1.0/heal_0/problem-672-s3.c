#include <stdio.h>

int max_of_three(int a, int b, int c) {
    int max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

int main() {
    int x = 10, y = 20, z = 30;
    int result = max_of_three(x, y, z);
    printf("The maximum number is: %d\n", result);
    return 0;
}