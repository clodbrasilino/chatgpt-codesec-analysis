#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int digit_distance(int num1, int num2) {
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
    printf("The digit distance is: %d\n", digit_distance(234, 489));
    printf("The digit distance is: %d\n", digit_distance(1, 1));
    printf("The digit distance is: %d\n", digit_distance(7, 0));
    return 0;
}