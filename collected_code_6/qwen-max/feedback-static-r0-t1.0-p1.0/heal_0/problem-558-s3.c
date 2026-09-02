#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int digit_distance(int num1, int num2) {
    if (num1 == 0 && num2 == 0) return 0;

    int distance = 0;
    while (num1 > 0 || num2 > 0) {
        int digit1 = num1 % 10;
        int digit2 = num2 % 10;
        distance += abs(digit1 - digit2);
        num1 /= 10;
        num2 /= 10;
    }
    return distance;
}

int main() {
    int a = 234;
    int b = 489;
    int result = digit_distance(a, b);
    printf("The digit distance is: %d\n", result);
    return 0;
}