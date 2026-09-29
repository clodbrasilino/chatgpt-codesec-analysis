#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int num1 = 10, num2 = 20;
    int result = max(num1, num2);
    printf("The maximum is %d\n", result);
    return 0;
}