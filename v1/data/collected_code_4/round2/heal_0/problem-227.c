#include <stdio.h>

int findMin(int num1, int num2, int num3) {
    int min = num1;

    if(num2 < min) {
        min = num2;
    }
    if(num3 < min) {
        min = num3;
    }

    return min;
}

int main() {
    int a = 10, b = 20, c = 30, min;

    min = findMin(a, b, c);
    
    printf("The minimum number is: %d\n", min);

    return 0;
}