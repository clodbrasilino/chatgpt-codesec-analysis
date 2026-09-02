#include <stdio.h>

int count_equal_numbers(int a, int b, int c) {
    if (a == b && b == c) {
        return 3;
    } else if (a == b || b == c || a == c) {
        return 2;
    }
    return 0;
}

int main(void) {
    int x = 5, y = 7, z = 5;
    printf("Equal count: %d\n", count_equal_numbers(x, y, z));
    return 0;
}