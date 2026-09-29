#include <stdio.h>

int max_of_two(int num1, int num2) {
    if(num1 > num2)
        return num1;
    else
        return num2;
}

int main() {
    int a = 10;
    int b = 20;
    int max;

    max = max_of_two(a, b);

    printf("Max: %d\n", max);

    return 0;
}