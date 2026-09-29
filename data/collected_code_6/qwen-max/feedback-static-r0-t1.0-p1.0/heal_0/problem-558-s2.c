#include <stdio.h>
#include <stdlib.h>

int abs(int x) {
    return x < 0 ? -x : x;
}

int digitDistance(int num1, int num2) {
    int sum = 0, diff;
    while (num1 > 0 || num2 > 0) {
        diff = abs((num1 % 10) - (num2 % 10));
        sum += diff;
        num1 /= 10;
        num2 /= 10;
    }
    return sum;
}

int main() {
    int num1 = 234, num2 = 489;
    printf("Digit distance: %d\n", digitDistance(num1, num2));
    return 0;
}