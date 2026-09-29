#include <stdio.h>

int highestPowerOf2(int n) {
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n = n + 1;
    return n >> 1;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    int result = highestPowerOf2(number);
    printf("Highest power of two less than or equal to %d is %d\n", number, result);
    return 0;
}