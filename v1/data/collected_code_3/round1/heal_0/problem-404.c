#include <stdio.h>

int findMin(int num1, int num2) {
    if(num1 < num2)
        return num1;
    else
        return num2;
}

int main() {
    int a = 10;
    int b = 20;
    int min;

    min = findMin(a, b);

    printf("Minimum of %d and %d is %d\n", a, b, min);

    return 0;
}