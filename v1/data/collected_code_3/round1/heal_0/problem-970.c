#include <stdio.h>

int findMin(int num1, int num2) {
    if(num1 < num2)
        return num1;
    else
        return num2;
}

int main() {
    int a = 10, b = 20, min;

    min = findMin(a, b);

    printf("Minimum number is %d\n", min);

    return 0;
}