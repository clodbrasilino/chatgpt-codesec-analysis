#include <stdio.h>

int min_of_two(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    int num1 = 10;
    int num2 = 20;
    int result = min_of_two(num1, num2);
    printf("Minimum: %d\n", result);
    return 0;
}