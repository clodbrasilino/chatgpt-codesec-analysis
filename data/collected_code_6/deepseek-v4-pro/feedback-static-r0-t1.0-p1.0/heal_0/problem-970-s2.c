#include <stdio.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    int num1 = 5;
    int num2 = 10;
    int result = min(num1, num2);
    printf("Minimum: %d\n", result);
    return 0;
}