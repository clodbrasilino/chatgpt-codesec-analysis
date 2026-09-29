#include <stdio.h>
#include <stdlib.h>

int digit_distance(int num1, int num2) {
    int distance = 0;
    num1 = abs(num1);
    num2 = abs(num2);
    
    while (num1 > 0 || num2 > 0) {
        int d1 = num1 % 10;
        int d2 = num2 % 10;
        distance += abs(d1 - d2);
        num1 /= 10;
        num2 /= 10;
    }
    
    return distance;
}

int main(void) {
    int num1, num2;
    if (scanf("%d %d", &num1, &num2) == 2) {
        printf("%d\n", digit_distance(num1, num2));
    }
    return 0;
}