#include <stdio.h>

int find_minimum(int a, int b, int c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

int main(void) {
    int num1 = 10;
    int num2 = 5;
    int num3 = 8;
    int min_val = 0;

    min_val = find_minimum(num1, num2, num3);

    printf("Minimum value is: %d\n", min_val);

    return 0;
}