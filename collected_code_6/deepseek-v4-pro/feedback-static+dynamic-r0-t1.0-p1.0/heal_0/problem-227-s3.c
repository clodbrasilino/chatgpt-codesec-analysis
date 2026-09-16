#include <stdio.h>

int minimum_of_three(int a, int b, int c) {
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
    int num1 = 15;
    int num2 = 7;
    int num3 = 22;
    
    int result = minimum_of_three(num1, num2, num3);
    printf("Minimum: %d\n", result);
    
    return 0;
}